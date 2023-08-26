/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
             //BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x
#define TOKEN "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x" // Your Ubidots TOKEN
#define WIFINAME "NETLIFE-RIVERA" //Your SSID
#define WIFIPASS "0909039109" // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  client.ubidotsSubscribe("esp8266","temperature"); //Insert the dataSource and Variable's Labels
  }

void loop() 
{
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("esp8266","temperature"); //Insert the dataSource and Variable's Labels
      }
  client.loop();
  delay(10000);
  }
