#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);

int UV_Val_RAMBAL;
int sensor1=0;
int sensor2=0;
int sensor3 =0;
int sensor4 =0;
void setup()
{
 //asignacion de comunicacion de datos entre arduino y antena bt
  Serial.begin(9600);
  dht.begin();
}
void loop()
{
  
  //sensor1 = (analogRead(A0)*48875)/100000;
  sensor1= dht.readTemperature();
  sensor2 = dht.readHumidity();
  sensor3 = (analogRead(A2)*100)/1024;
  //sensor4 = (analogRead(A3)*100)/1024;
  UV_Val_RAMBAL = analogRead(A3);
  
  if(UV_Val_RAMBAL < 10)  
  { sensor4=0;  }
  else  {  if(UV_Val_RAMBAL < 46)  {
    sensor4=1;  }
  else  {  if(UV_Val_RAMBAL < 65)  {
    sensor4=2;  }
  else  {  if(UV_Val_RAMBAL < 83)  {
    sensor4=3;  }
  else  {  if(UV_Val_RAMBAL < 103)  {
    sensor4=4;  }
  else  {  if(UV_Val_RAMBAL < 124)  {
    sensor4=5;  }
  else  {  if(UV_Val_RAMBAL < 142)  {
    sensor4=6;  }
  else  {  if(UV_Val_RAMBAL < 163)  {
    sensor4=7;  }
  else  {  if(UV_Val_RAMBAL < 180)  {
    sensor4=8;  }
  else  {  if(UV_Val_RAMBAL < 200)  {
    sensor4=9;  }
  else  {  if(UV_Val_RAMBAL < 221)  {
    sensor4=10;  }
  else  {  if(UV_Val_RAMBAL < 239)  {
    sensor4=11;  }
  else  {
    sensor4=12;  }
     }}}}}}}}}}}

        Serial.print(String(" ")+String(sensor1)+":"+String(sensor2)+":"+String(sensor3)+":"+String(sensor4));  
        delay(5000);

}
//98D332706D83
