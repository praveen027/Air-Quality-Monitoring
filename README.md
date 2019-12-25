# Air Quality and Environment Monitoring System
A simple handy device to show the AQI index , concentration of other gases along with Temperature, Humidity, Sound Level, Light Intensity and Rain.

## Getting Started
IoT based environment monitoring system is designed by interfacing different sensors with Arduino Mega. The data obtained from the sensors are accessed using the Wi-Fi module (ESP8266 12ENodeMCU) to collect real-time data on one of the servers. Here, ThingSpeak which is an IoT platform is used to collect data from the Wi-Fi module. The whole system is made wireless 


### Prerequisites

* CP2102 driver- available in the repository for windows machine
* Fritzing software- online available for free
* Arduino IDE - online free software available and easy installation for windows 

### Installing

For ubuntu 18.04 LTS users-
Download Arduino IDE package from the Download page of Arduino official website. Make sure to download the right version 32-bit or 64-bit depending upon your operating system.
Navigate to downloads in terminal.
To uncompress the archived folder, run the following command in Terminal:

```
$ tar –xf [Compressed-filename]
```
Run the following command in Terminal as sudo to install Arduino.

```
$ sudo ./install.sh
```
To begin, we’ll need to update the board manager with a custom URL. Open up Arduino IDE and go to File > Preferences. Then, copy below URL into the Additional Board Manager URLs text box situated on the bottom of the window:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
Hit OK. Then navigate to the Board Manager by going to Tools > Boards > Boards Manager. There should be a couple of new entries in addition to the standard Arduino boards. Filter your search by typing esp8266. Click on that entry and select Install. 
Once the installation has completed, a small INSTALLED text will appear next to the entry. You can now close the Board Manager.
Open Arduino IDE and select NodeMCU 0.9 (ESP-12 Module) option under your Arduino IDE > Tools > Board menu.
Now, plug your ESP8266 NodeMCU into your computer via micro-B USB cable. Once the board is plugged in, it should be assigned a unique COM port. On Windows machines, this will be something like COM#. Select this serial port under the Arduino IDE > Tools > Port menu. Also select the Upload Speed: 115200
More attention needs to be given to selecting board, choosing COM port and selecting 

Upload speed. You may get espcomm_upload_mem error while uploading new sketches, if failed to do so.
Finally, you need to download drivers on your computer in order to use the COM# port.   
For this project we used cp2102 driver.

## Hardware Components

* MQ 9
* MQ 135
* DHT 11
* LM-393
* YL-83
* NodeMCU LUA ESP8266 ESP-12E
* Arduino board
* HC 4051 MUX IC
* Bread board or GCB


## Deployment

To be able to send alert messages via thingSpeak go to the given site:
<br/>
https://in.mathworks.com/help/thingspeak/use-ifttt-to-send-text-message-notification.html .
<br/>
If you want your system to send a call configure Twilio account as mentioned here:
<br/>
https://community.thingspeak.com/tutorials/twilio/make-calls-with-twilio-using-the-thinghttp-app/


## Built With

* [IFTTT](https://ifttt.com/) - The web service used
* [Twilio](https://www.twilio.com/) -Message service
* [ThingSpeak](https://thingspeak.com/) - Used to view data online

## Connections

### Arduino Mega to sensors
* a0 -> mq135 (analog)
* a1 -> mq 9  (analog)
* a2 -> yl-83 (analog)
* a3 -> lm-393 (analog)
* a4 -> sound sensor (analog)
* ~6 -> dht 11 (digital)

### LCD to Arduino

* RS -> ~12
* Enable -> ~11 
* D4 -> ~5
* D5 -> ~4
* D6 -> ~3
* D7 -> ~2


### ESP8266 to 4051 MUX

*D4 -> S0 (A)
* D3 -> S1 (B)
* D2 -> S2 (C)
* A0 -> Common
* 3.3v -> VCC
* G -> GND
* G -> Inhibit
* G -> VEE

<br/>
3 select pins, labeled A B and C (These are digital pins)
<br/>
A Common pin
<br/>
8 option pins (labeled X0 - X7)

### 4051 MUX to sensors

* X1 -> mq135 (analog)
* X0 -> mq 9  (analog)
* X2 -> yl-83 (analog)
* X3 -> lm-393 (analog)

## Contributing

Please read [CONTRIBUTING.md](https://www.github.com/praveen027) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **Praveen Kukreja** - [view profile](https://github.com/praveen027)
* **Deep Pujara** - [view profile](https://github.com/deeppujara)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* **Billie Thompson** - *Templates* - [PurpleBooth](https://github.com/PurpleBooth)
* **Máté Huszárik** -[D3.js tutorial](https://blog.risingstack.com/tutorial-d3-js-calendar-heatmap/)

