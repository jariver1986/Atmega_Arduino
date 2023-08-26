#include "UbidotsESPMQTT.h"
             //BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x
#define TOKEN "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x" // Your Ubidots TOKEN
#define WIFINAME "NETLIFE-RIVERA" //Your SSID
#define WIFIPASS "0909039109" // Your Wifi Pass
Ubidots client(TOKEN);
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
String incomingString1="";
String incomingString2="";
String incomingString3="";
String incomingString4="";
String incomingString5="";
String incomingString6="";
String incomingString7="";
String incomingString8="";
float valor1=0;
float valor2=0;
float valor3=0;
float valor4=0;
float valor5=0;
float valor6=0.00000;
float valor7=0.00000;
float valor8=0;
void setup() 
{
  Serial.begin(115200);
  Serial1.begin(115200);
  
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);  
}

void loop() 
{
  //modelo
  //1011.93@28.80@1@0@30.34@-2.22367@-7.992608@0@
  if (Serial.available() > 2) 
  {
    incomingString1 = Serial.readStringUntil('@');
    incomingString2 = Serial.readStringUntil('@');
    incomingString3 = Serial.readStringUntil('@');
    incomingString4 = Serial.readStringUntil('@');
    incomingString5 = Serial.readStringUntil('@');
    incomingString6 = Serial.readStringUntil('@');
    incomingString7 = Serial.readStringUntil('@');
    incomingString8 = Serial.readStringUntil('@');
    
    if((incomingString1!=0)||(incomingString2!=0)||(incomingString3!=0))
    {
      Serial.print("He recibido: ");
      Serial.println(incomingString6);
      Serial.print("He recibido: ");
      Serial.println(incomingString7);
      
      valor1 = incomingString1.toFloat();
      valor2 = incomingString2.toFloat();
      valor3 = incomingString3.toFloat();
      valor4 = incomingString4.toFloat();
      valor5 = incomingString5.toFloat();
      valor6 = incomingString6.toFloat();
      valor7 = incomingString7.toFloat();
      valor8 = incomingString8.toFloat();
      // put your main code here, to run repeatedly:
      if(!client.connected())
      {
          client.reconnect();
          }
      
      // Publish values to 2 different data sources
      
      client.add("presion", valor1); 
      client.add("temperatura", valor2); 
      client.add("uv", valor3); 
      client.ubidotsPublish("Datos1");
      client.add("lluvia", valor4);
      client.add("gas", valor5);
      client.add("latitud",  valor6*100000);
      client.add("longitud", valor7*100000);
      client.add("x", valor8);
      client.ubidotsPublish("Datos2");
      client.loop();
    }
  }
  
  delay(1000);
}
