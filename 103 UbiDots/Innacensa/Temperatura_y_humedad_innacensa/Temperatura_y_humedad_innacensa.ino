#include "Ubidots.h"
#include<SimpleDHT.h>
                            
const char* UBIDOTS_TOKEN = "BBFF-fhUIisjZvgMABgl8BiYMZPIEHOOSSX";  // Put here your Ubidots TOKEN
const char* DEVICE_TYPE = "temperatura-humedad-innacensa";     // Edit here your device type label
const char* WIFI_SSID = "Mu"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "0909039109"; // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
float Valor_Temperatura = 0;
float Valor_Humedad = 0;
int pinDHT11 = 16;
SimpleDHT11 dht11(pinDHT11);
int contador=0;

void setup() 
{
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);  
  ubidots.setDeviceType(DEVICE_TYPE);
  pinMode(pinDHT11, INPUT);
}

void loop() 
{
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, data)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  float decimal=0.0;
  decimal=(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]);
  float dato= temperature+decimal/10;
  Serial.print("temperatura: ");
  Serial.print(String(dato));
  Serial.print(" C, ");
  Serial.print("Humedad: ");
  Serial.print((int)humidity); 
  Serial.println(" H");  
  
  ubidots.add("Temperatura", dato);
  ubidots.add("Humedad",humidity );
  

  bool bufferSent = false;
  bufferSent = ubidots.send("");  // Will send data to a device label that matches the device Id
  delay(5000);
  
} 
