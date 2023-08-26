// This example sends data to multiple variables to
// Ubidots through HTTP protocol, and uses Device Types feature

// IMPORTANT: Device type are only supported through HTTP

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* DEVICE_TYPE = "Pruebas Arduino";     // Edit here your device type label
const char* WIFI_SSID = "NETLIFE-RIVERA";           // Put here your Wi-Fi SSID
const char* WIFI_PASS = "0909039109";           // Put here your Wi-Fi password
                              //3438712727070596
const char* UBIDOTS_TOKEN = "47hviP5NonBRFq98IdDshNWJFO6T8uVo7cJZt";  // Put here your Ubidots TOKEN
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

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
  ubidots.setDeviceType(DEVICE_TYPE);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
  delay(20000);
  float value1 = random(0, 9) * 10;
  float value2 = random(0, 9) * 100;
  float value3 = random(0, 9) * 1000;
  ubidots.add("Columna2", value1);  // Change for your variable name
  ubidots.add("Columna3", value2);
  ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }
  Serial.println("Dato enviado");
  
}
