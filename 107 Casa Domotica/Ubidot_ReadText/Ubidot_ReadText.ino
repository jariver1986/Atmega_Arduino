#include "UbidotsESPMQTT.h"
#include<SimpleDHT.h>
#include<ESP8266WIFI.h>
#include <SoftwareSerial.h>
             //BBFF-6v0y8D7JEHDKyWcqdJhGkXAsbK4DYY
#define TOKEN "BBFF-6v0y8D7JEHDKyWcqdJhGkXAsbK4DYY" // Your Ubidots TOKEN
#define WIFINAME "NETLIFE-RIVERA" //Your SSID
#define WIFIPASS "0909039109" // Your Wifi Pass
//#define WIFINAME "INNACENSA" //Your SSID
//#define WIFIPASS "innacensa." // Your Wifi Pass

Ubidots client(TOKEN);
SoftwareSerial mySerial(13,15); // RX, TX 

int pinDHT11 = 14;
//SimpleDHT11 dht11(pinDHT11);
SimpleDHT11 dht11(pinDHT11);
//Sensor de calidad aire MQ135
int MQ135=0;

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(9600);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  Serial.print("mac : ");
  Serial.print(WiFi.macAddress());
  }

void loop() 
{
  //++++++++++++++++++++++++++++++++++++++++DHT11
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, data)) != SimpleDHTErrSuccess) 
  {
    //Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  float decimal=0.0;
  decimal=(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]);
  float dato= temperature+decimal/10;
  //Serial.print("temperatura: ");
  //Envio por D8
  mySerial.print(String(dato)); //Envio por D8
  mySerial.print("@ ");
  //Serial.print("Humedad: ");
  mySerial.print((int)humidity); 
  mySerial.println(";_#");
  //++++++++++++++++++++++++++++++++++++++++++MQ135

  //+++++++++++++++++++++++++++++++++++++++++++++IOT++++++++++++++++++++++++++++++++++
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
      client.reconnect();
  }
  // Publish values to 2 different data sources
  
  client.add("stuff", dato); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("source1");
  client.add("stuff",dato );
  client.add("more-stuff", humidity);
  client.ubidotsPublish("source2");
  //client.add("stuff", MQ135); //Insert your variable Labels and the value to be sent
  //client.ubidotsPublish("source3");
  client.loop();
  delay(10000);
  
  }
