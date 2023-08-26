// This example sends data to multiple variables to
// Ubidots through TCP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Mu";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "0909039109";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() 
{
  //Poceso de sensoores

  //Asignacion de variables
  float value1 = random(0, 9) * 10;  
  ubidots.addContext("Ambiente", "caliente");
  char* context = (char*)malloc(sizeof(char) * 60);
  ubidots.getContext(context);
  ubidots.add("T", value1,context);  // Change for your variable name
  bool bufferSent = false;
  bufferSent = ubidots.send("context");  // Will send data to a device label that matches the device ID
  if (bufferSent) 
  {
    // Do something if values were sent properly
    Serial.println("Values sent by the device T");
  }

  float value2 = random(0, 9) * 100;  
  ubidots.addContext("Ambiente", "humedo");
//  char* context = (char*)malloc(sizeof(char) * 60);
  ubidots.getContext(context);
  ubidots.add("H", value2,context);  // Change for your variable name
//  bool bufferSent = false;
  bufferSent = ubidots.send("context");  // Will send data to a device label that matches the device ID
  if (bufferSent) 
  {
    // Do something if values were sent properly
    Serial.println("Values sent by the device H");
  }

  float value3 = random(0, 9) * 1000;  
  if(value3>3000)
    ubidots.addContext("Calidad Aire", "bueno");
  else
    ubidots.addContext("Calidad Aire", "malo");
    
//  char* context = (char*)malloc(sizeof(char) * 60);
  ubidots.getContext(context);
  ubidots.add("G", value3,context);  // Change for your variable name
//  bool bufferSent = false;
  bufferSent = ubidots.send("context");  // Will send data to a device label that matches the device ID
  if (bufferSent) 
  {
    // Do something if values were sent properly
    Serial.println("Values sent by the device G");
  }

  delay(10000);
}
