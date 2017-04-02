# DHT22

## Default Wiring
| DHT22|ESP8266   |
|:----------:|:-------------:|
|1. Pin|VCC|
|2. Pin|GPIO0|
|3. Pin|Not Connected|
|4. Pin|GND|

Pins on DHT are counted from front view, left to right.

For more information see connection scheme below (or in Repo):

![connection](https://github.com/WiFiHomeControl/DHT22/blob/master/DHT_Scheme_Steckplatine.png)


## Usage

1. Load the `DHT.ino` on your Arduino - but change WiFi Credentials first!
2. If you havent installed NodeJS yet, install it!
3. Modify the `ReadDHT22.js` so the IP and Port matches your ESP!
4. run `npm install`
5. run the `ReadDHT22.js` script with `node ReadDHT22.js`

## Customization

There are several variables in both scripts which helps to customize the script!

#### Arduinos DHT22.ino
`#define DHTTYPE DHT22` - Set to your specific DHT Type

`const bool fahrenheit` - Set the unit you want the temperature measurements

`const char* ssid` - Set your WiFi's SSID

`const char* password` - Set your WiFi's Password

`WiFiServer server(1337)` - Set the Port (1337 is default)

`const int DHTPin = 0` - Set the Pin, the DHT Data Pin is connected to the ESP

#### NodeJS Script

`const ip` - Set ESP's IP (or mDNS Domain)

`const port` - Set ESP's Port (which you have specified in Arduinos DHT22.ino)
