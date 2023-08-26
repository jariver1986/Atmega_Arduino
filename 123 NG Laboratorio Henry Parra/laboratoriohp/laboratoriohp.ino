/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include<SimpleDHT.h>
#include <Wire.h>
#include <SoftwareSerial.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-LXGwPPTaT5yeOocJNYYUFFJeBUmQmu" // Your Ubidots TOKEN
//#define WIFINAME "NETLIFE-RIVERA" //Your SSID
//#define WIFIPASS "0909039109" // Your Wifi Pass
#define WIFINAME "NETLIFE-PARRA" //Your SSID
#define WIFIPASS "0913233904" // Your Wifi Pass


Ubidots client(TOKEN);
SoftwareSerial mySerialbt(13,15); // RX-D7, TX-D8 Serial Node remapeado 
/****************************************
 * Auxiliar Functions
 ****************************************/
int pinDHT11 = 14;
int contador=0;
int centinela=0;
int contador2=0;


SimpleDHT11 dht11(pinDHT11);

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
  mySerialbt.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  Serial.print("temperatura: ");
  Serial.print(String(temperature));
  Serial.print(" C, ");
  Serial.print("Humedad: ");
  Serial.print((int)humidity); 
  Serial.println(" H");
  
  
  
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
  if((centinela==0)&&(contador2<5))
  {
    contador2++; 
  }
  else  {centinela=1;}
  
  // Publish values to 2 different data sources
  if((contador>90)||(centinela==0))
  {
    
    client.add("temperatura", temperature); //Insert your variable Labels and the value to be sent
    client.ubidotsPublish("Laboratoriohp");
    client.add("humedad", humidity);
    client.ubidotsPublish("source2");
    client.loop();
    Serial.println("Dato enviado a web temepratura: " + String(temperature));//Informacion a PC
    mySerialbt.println("_@"+String(temperature)+"@;");//Actualizo dato a BT
    contador=0;
  }
  contador++;
  delay(10000);
  }
