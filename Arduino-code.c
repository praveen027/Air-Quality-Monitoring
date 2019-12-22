#include <SimpleDHT.h>
#include<LiquidCrystal.h>
SimpleDHT11 dht11;
int p;
int t;
int h;
int a;
int r;
int ldr;
float g;
int MicValue1 = 0;
int MicValue2 = 0;
int MicPin = A4;
int pinDHT11 = 6;
int siranPin = 10;
int ledPin=13;
int sensorValue;
int sensorvalue1;
float sensorvoltage;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte lev1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
};

byte lev2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
};

byte lev3[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
};

byte lev4[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
};

byte lev5[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
};

byte lev6[8] = {
  0b00111,
  0b00111,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

void setup() 
{
  pinMode (siranPin, OUTPUT);
  pinMode (MicPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16,4);
}
void loop() 
{  
  //DHT 11 Sensor Output Display Process
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    return;
  }
  t=(int)temperature;
  h=(int)humidity;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T: ");
  lcd.setCursor(3,0);
  lcd.print((int)temperature);
  lcd.createChar(5,lev6);
  lcd.setCursor(5,0);
  lcd.write(byte(5));
  lcd.setCursor(6,0);
  lcd.print("C");
  lcd.createChar(4,lev5);
  lcd.setCursor(8,0);
  lcd.write(byte(4)); 
  lcd.setCursor(10,0);
  lcd.print("H: ");
  lcd.setCursor(13,0);
  lcd.print((int)humidity);
  lcd.setCursor(15,1);
  lcd.print("%");
  //DHT 11 Sensor Output Display Process Ends

  //AQI Sensor Output Display Process
  sensorValue = analogRead(A0);
  a=sensorValue;       
  lcd.setCursor(0,1);
  lcd.print("A:");
  if(a>0 && a<250)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(2,1);
    lcd.write(byte(0)); 
  }
   else if(a>249 && a<500)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(2,1);
    lcd.write(byte(0)); 
    lcd.createChar(1,lev2);
    lcd.setCursor(3,1);
    lcd.write(byte(1)); 
  }
  else if(a>499 && a<750)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(2,1);
    lcd.write(byte(0)); 
    lcd.createChar(1,lev2);
    lcd.setCursor(3,1);
    lcd.write(byte(1)); 
    lcd.createChar(2,lev3);
    lcd.setCursor(4,1);
    lcd.write(byte(2)); 
  }
   else if(a>749 && a<1001)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(2,1);
    lcd.write(byte(0)); 
    lcd.createChar(1,lev2);
    lcd.setCursor(3,1);
    lcd.write(byte(1)); 
    lcd.createChar(2,lev3);
    lcd.setCursor(4,1);
    lcd.write(byte(2)); 
    lcd.createChar(3,lev4);
    lcd.setCursor(5,1);
    lcd.write(byte(3)); 
  }
  //AQI Sensor Output Display Process Ends

  lcd.createChar(4,lev5);
  lcd.setCursor(7,1);
  lcd.write(byte(4)); 

  //CO Sensor Output Display Process
  sensorvalue1 = analogRead(A1);
  sensorvoltage = (sensorvalue1*5.0)/1024;
  g=sensorvoltage;
  lcd.setCursor(9,1);
  lcd.print("CO:");
  if(g>0 && g<0.5)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(12,1);
    lcd.write(byte(0)); 
  }
   else if(g>0.3 && g<0.9)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(12,1);
    lcd.write(byte(0)); 
    lcd.createChar(1,lev2);
    lcd.setCursor(13,1);
    lcd.write(byte(1)); 
  }
  else if(g>0.7 && g<1.3)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(12,1);
    lcd.write(byte(0)); 
    lcd.createChar(1,lev2);
    lcd.setCursor(13,1);
    lcd.write(byte(1)); 
    lcd.createChar(2,lev3);
    lcd.setCursor(14,1);
    lcd.write(byte(2)); 
  }
   else if(g>1.1 && g<1.7)
  {
    lcd.createChar(0,lev1);
    lcd.setCursor(12,1);
    lcd.write(byte(0)); 
    lcd.createChar(1,lev2);
    lcd.setCursor(13,1);
    lcd.write(byte(1)); 
    lcd.createChar(2,lev3);
    lcd.setCursor(14,1);
    lcd.write(byte(2)); 
    lcd.createChar(3,lev4);
    lcd.setCursor(15,1);
    lcd.write(byte(3)); 
  }
  //CO Sensor Output Display Process Ends

  //Rain Sensor Output Display Process
  r = analogRead(A2);
  lcd.setCursor(0,2);
  lcd.print("Rain:");
  if (r<500)
  {
    lcd.setCursor(5,2);
    lcd.print("Yes");
  }
  else
  {
    lcd.setCursor(6,2);
    lcd.print("No");
  }
  //Rain Sensor Output Display Process

  lcd.createChar(4,lev5);
  lcd.setCursor(8,2);
  lcd.write(byte(4));

  //Light Sensor Output Display Process
  ldr = analogRead(A3);
  if (ldr<250)
  {
    lcd.setCursor(9,2);
    lcd.print("L: Low");
  }
  else 
  {
    lcd.setCursor(9,2);
    lcd.print("L:High");
  }
  //Light Sensor Output Display Process Ends

  //Sound Sensor Output Display Process
  MicValue1 = analogRead (MicPin);
  MicValue2 = analogRead (MicPin);
  if (abs(MicValue1-MicValue2)>50)
   {
     digitalWrite (siranPin, HIGH);
     delay(500);
     digitalWrite (siranPin, LOW);
     lcd.setCursor(0,3);
     lcd.print("Sound:High");
   }
   else 
   {
    lcd.setCursor(0,3);
    lcd.print("Sound: Low");
   }
   //Sound Sensor Output Display Process Ends
}
