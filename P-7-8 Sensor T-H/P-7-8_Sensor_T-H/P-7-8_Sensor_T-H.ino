//Descarga de libreria
//https://github.com/winlinvip/SimpleDHT

#include <SimpleDHT.h>
SimpleDHT11 sensor;
byte T=0;
byte H=0;
void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
    sensor.read(2,&T,&H,NULL);
    Serial.print("Temperatura= ");
    Serial.println((int)T);
    Serial.print("Humedad= ");
    Serial.println((int)H);
    delay(2000);
}
