#include <Ultrasonic.h>
#include <Servo.h>

Ultrasonic ultrasonic(12,13); 
Servo control1;
int centinela=0;
int distancia=0;
int estado=0;
void setup() 
{
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    control1.attach(2);
    control1.write(60);
    Serial.begin(9600);
    delay(500);
}

void loop() 
{
  //////////////////////////////////Sensor ultrasonico
    distancia=ultrasonic.read();
    if (distancia < 10)
    {
      delay(100);
      distancia=ultrasonic.read();
       if (distancia < 10)
        {
          centinela=1;    
        } 
    }
    if (distancia > 10)
    {
    centinela=0;
    }
    
    if(centinela==1)
    {
      control1.write(30);
      delay(400);
    }
    if(centinela==0)
    {
      control1.write(60);
      delay(400);
    }
  //////////////////////////////////Sensor infrarrojo
  /*estado=digitalRead(3);
  if(estado==LOW)
  {
    delay(100);
    int estado=digitalRead(3);
    if(estado==LOW)
    {
      control1.write(10);
      delay(500);
      control1.write(60);
      delay(500);
    }
  }*/
  delay(100);
}
