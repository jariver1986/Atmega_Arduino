#include <Ultrasonic.h>
Ultrasonic sensor(8,9,23200);
int dato=0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
    dato=sensor.Ranging(CM);
    Serial.print("Distancia= ");
    Serial.println(dato);
    delay(1000);
}
