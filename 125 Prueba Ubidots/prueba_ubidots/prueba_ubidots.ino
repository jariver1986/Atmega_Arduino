
#include "UbidotsESPMQTT.h"
#include<SimpleDHT.h>
#include<ESP8266WIFI.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
             //BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x  
#define TOKEN "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x" // Your Ubidots TOKEN
//#define WIFINAME "NETLIFE-RIVERA_EXT" //Your SSID
#define WIFINAME "eterno" //Your SSID
//#define WIFINAME "NETLIFE-RIVERA" //Your SSID
#define WIFIPASS "0909039109" // Your Wifi Pass

//#define WIFINAME "AndroidAP63E8" //Your SSID
//#define WIFIPASS "marcoscomputercars" // Your Wifi Pass
//#define WIFINAME "proyecto200816" //Your SSID
//#define WIFIPASS "proyecto200816." // Your Wifi Pass

Ubidots client(TOKEN);

int pinDHT11 = 14;
SimpleDHT11 dht11(pinDHT11);
//Sensor de calidad aire MQ135
int MQ135=0;
int contador=05;
int habilita=0;
int contador2=10;
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
  Serial.print("mac : ");
  Serial.print(WiFi.macAddress());
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
   mlx.begin();  
  pinMode(D5, INPUT);
  pinMode(D6, OUTPUT);
   pinMode(D7, OUTPUT);
   //digitalWrite(D5, LOW);
  }

void loop() 
{
  //Serial.print("mac : ");
  //Serial.print(WiFi.macAddress());
  //++++++++++++++++++++++++++++++++++++++++DHT11
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;
  /*if ((err = dht11.read(&temperature, &humidity, data)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }*/
  float decimal=0.0;
  decimal=(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]);
  float dato= mlx.readObjectTempC();//temperature+decimal/10;
  Serial.print("T = ");
  Serial.println(mlx.readObjectTempC());
  humidity=8;
  Serial.print("temperatura: ");
  Serial.print(String(dato));
  Serial.print(" C, ");
  Serial.print("Humedad: ");
  Serial.print((int)humidity); 
  Serial.println(" H");
  //++++++++++++++++++++++++++++++++++++++++++MQ135
  MQ135=9;//analogRead(A0);
  Serial.println(MQ135);
  //+++++++++++++++++++++++++++++++++++++++++++++IOT++++++++++++++++++++++++++++++++++
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
      client.reconnect();
  }
  // Publish values to 2 different data sources

     contador++; 


     contador2++;
    client.add("stuff", contador); //Insert your variable Labels and the value to be sent
    client.ubidotsPublish("source1");
    client.add("stuff",contador2 );
    //client.add("more-stuff", humidity);
    client.ubidotsPublish("source2");
    //client.add("stuff", MQ135); //Insert your variable Labels and the value to be sent
    //client.ubidotsPublish("source3");
   
   
   
  
  
  client.loop();
  delay(10000);
  
  
  }
