#include <hcsr04.h>

#define TRIG_PIN 12
#define ECHO_PIN 13

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);


int dato = 0;




void setup() 
{
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);

  
}

void loop() 
{
  if(Serial.available()>0)
  {
    dato = Serial.read();
    if(dato == '1')
    {
      digitalWrite(2,HIGH);
    }
    if(dato == '2')
    {
      digitalWrite(2,LOW);
    }
    if(dato == '3')
    {
      
    }
    if(dato == '4')
    {
      
    }
    if(dato == '5')
    {
      
    }
    if(dato == '6')
    {
      
    }
    if(dato == '7')
    {
      
    }
    if(dato == '8')
    {
      
    }
    dato=0;
  }
  Serial.println(hcsr04.ToString());
  delay(250);
}
