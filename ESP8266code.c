#include <ESP8266WiFi.h>
#include <DHT.h> // Including library for dht

#define DHTPIN 5 //pin where the dht11 is connected
#define ANALOG_INPUT A0

#define MUX_A D4
#define MUX_B D3
#define MUX_C D2
DHT dht(DHTPIN, DHT11);
int x;

String apiKey = "";//Enter the write API key of your thingSpeak channel inside inverted commas  
const char *ssid = "";//Enter the name of hotspot to which your ESP module will be connected such as your mobile hotspot name
const char *pass = "";  //write the password of that hotspot
const char* server = "api.thingspeak.com";   //server website to which data is uploaded
WiFiClient client;
void setup()
{
  x=0;
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);     
  pinMode(MUX_C, OUTPUT); 
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
}

void changeMux(int c, int b, int a) 
  {
    digitalWrite(MUX_A, a);
    digitalWrite(MUX_B, b);
    digitalWrite(MUX_C, c);
  }
float decide(int x)  //Since ESP has only one input analog pin we use multiplexing via hc 4051 IC to send multiple analog sensors data using switch statement
  {
    float value;
    switch(x)
      {
        case 1:
          changeMux(LOW, LOW, LOW);
          value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
        break;
        
        case 2:
          changeMux(LOW, LOW, HIGH);
          value = (analogRead(ANALOG_INPUT)*100)/1023; //Value of the sensor connected Option 1 pin of Mux
        break;
        
        case 3:
          changeMux(LOW, HIGH, LOW);
          value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
        break;
        
        case 4:
          changeMux(LOW, HIGH, HIGH);
          value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 3 pin of Mux
      }
      return value;
}

void loop() 
  {
    x++;
    if(x>4)
    {
      x=1;
    }
    float h;
    h= decide(x);
    if (isnan(h))
    {
      Serial.println("Failed to read from MQ-5 sensor!");
      return;
    }
    float hu = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(hu) || isnan(t))
      {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

    if (client.connect(server, 80)) 
      {
        String postStr = apiKey;
        postStr +="&field1=";
        postStr += String(t);
        postStr +="&field2=";
        postStr += String(hu);
          
        if (x==2)                 //multiplexing
          { 
              postStr += "&field3=";
          }
        else if(x==1)
          { 
              postStr += "&field4=";
          }
        else if(x==3)
          {
              postStr += "&field5=";
          }
        else if(x==4)
          {
              postStr += "&field6=";
          }
        postStr += String(h);
        postStr += "\r\n\r\n\r\n";
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
        Serial.print("Gas Level: ");
        Serial.println(h/1023*100);
        Serial.println("Data Send to Thingspeak");
    }
  client.stop();
  Serial.println("Waiting...");
  delay(1500);
}
