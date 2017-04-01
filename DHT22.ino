// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ArduinoJson.h>

//Define DHT Type
#define DHTTYPE DHT22

//Setting Network Credentials
const char* ssid = "<SSID HERE>";
const char* password = "<PASSWORD HERE>";

// Web Server on port 1337 (see WiFIHomeControl/README/Ports.md for more information about Ports!)
WiFiServer server(1337);

// DHT Sensor Pin
const int DHTPin = 0;

// Initialize DHT sensor
DHT dht(DHTPin, DHTTYPE);


void setup() {

  dht.begin();
  
  WiFi.begin(ssid, password);

  //Wait until WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Starting the web server
  server.begin();
  delay(10000);
}

void loop() {

  //Waiting for connection
  WiFiClient client = server.available();
  
  if (client) {
    //boolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n' && blank_line) {

            // Read temperature as Celsius
            // Read temperature as Fahrenheit (dht.readTemperature(true) for Fahrenheit)

            //Check if Read fails, send 500
            if (isnan(dht.readHumidity()) || isnan(dht.readTemperature())) {
              client.println("HTTP/1.1 500 Internal Server Error");
              client.println("Content-Type: application/json");
              client.println("Connection: close");
              client.println();
              return;         
            }

            //If it does not fail, send JSON with temperature and humidity
            StaticJsonBuffer<200> jsonBuffer;
            JsonObject& resp = jsonBuffer.createObject();
            resp["temperature"] = dht.readTemperature();
            resp["humidity"] = dht.readHumidity();

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: application/json");
            client.println("Connection: close");
            client.println();

            //Send WebPage
            resp.printTo(client);    
            break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }

    //ends connection
    delay(1);
    client.stop();
  }
}   
