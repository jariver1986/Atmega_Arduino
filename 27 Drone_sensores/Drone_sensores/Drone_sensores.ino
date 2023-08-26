#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);
int option;
int led = 13;
int sensor1=0;
int sensor2=0;
int sensor3 =0;
int sensor4 =0;
int conteo=0;
void setup()
{
 //asignacion de comunicacion de datos entre arduino y antena bt
  Serial.begin(9600);
  dht.begin();
}
void loop()
{
  
  sensor1 = (analogRead(A0)*48875)/100000;
  sensor2 = dht.readHumidity();
  sensor3 = (analogRead(A2)*100)/1024;
  sensor4 = (analogRead(A3)*100)/1024;
  if (Serial.available()>0)
  {
    option=Serial.read();
    if(option=='1') 
    {
      if(sensor1<50)
      {
        Serial.print("_"+String(sensor1)+"");  
      }
      if(sensor1>50)
      {
        Serial.print("T");
      }
    }
    if(option=='2') 
    {
      if(sensor2<50)
      {
        Serial.print("_"+String(sensor2)+"%");  
      }
      if(sensor2>50)
      {
        Serial.print("H");
      }
    }
    if(option=='3') 
    {
      if(sensor3<50)
      {
        Serial.print("_"+String(sensor3)+"%");  
      }
      if(sensor3>50)
      {
        Serial.print("C");
      }
    }
    if(option=='4') 
    {
      if(sensor4<50)
      {
        Serial.print("_"+String(sensor4)+"%");  
      }
      if(sensor4>50)
      {
        Serial.print("U");
      }
    }
    option=0;
  }
}
//98D332706D83
