/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Mu"; // Put here your Wi-Fi SSID
//const char* WIFI_SSID = "Mu2"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "0909039109"; // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() 
{
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  pinMode(5,INPUT); //PIN D1
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() 
{
//++++++++++++++++++++++++++++++++++++++++++++SENSOR HUMEDAD TIERRA
  int estado=digitalRead(5);
  if(estado==HIGH)
  {
    Serial.println("seco ");
    ubidots.add("tierra",0);  // Change for your variable name
  }
  else 
  {
    Serial.println("humedo ");
    ubidots.add("tierra",1);  // Change for your variable name
  }
       
//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS TX

  
  
  float value2 = random(0, 9) * 100;
  //float value3 = random(0, 9) * 100;
  
  ubidots.add("UV1", value2);
  //ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send("esp8266_principal");  // Will send data to a device label that matches the device Id

  if (bufferSent) 
  {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(10000);
} 
