#include <Ultrasonic.h>
Ultrasonic ultrasonic(2,3);//Trig,Echo
int distancia=100;
int dato=0;
void setup() 
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(4,LOW);
  
}

void loop() 
{
  
  distancia = ultrasonic.read();
    delay(100);
    Serial.println("Distancia= "+String(distancia));
    
    if((distancia>75)&&(distancia<100))
    {
      digitalWrite(13,LOW);
      digitalWrite(12,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      
      
    }
    if((distancia>50)&&(distancia<75))
    {
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
      
      
    }
    if((distancia>25)&&(distancia<50))
    {
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(10,HIGH);
      
    }
    if((distancia>5)&&(distancia<25))
    {
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(4,HIGH);
      delay(200);
      digitalWrite(4,LOW);
      delay(200);
      digitalWrite(4,HIGH);
      delay(200);
      digitalWrite(4,LOW);
      delay(200);
    }
    if(distancia>100)
    {
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(10,HIGH);
    }

}
