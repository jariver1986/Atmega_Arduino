#include <Ultrasonic.h>
int sonido=8;

int distancia=0;
int distancia2=0;


Ultrasonic ultrasonic(6,7,23200); // (Trig PIN,Echo PIN, TIMEOUT)
Ultrasonic ultrasonic2(9,10,23200); // (Trig PIN,Echo PIN, TIMEOUT)
//TIMEOUT = (CENTIMETROS)*(58)

void setup() 
{
  Serial.begin(9600);  
  pinMode(sonido, OUTPUT); 
  pinMode(13, OUTPUT); 
}

void loop()
{
  distancia = ultrasonic.Ranging(CM);
  distancia2 = ultrasonic2.Ranging(CM);
Serial.print(distancia); // CM or INC
  Serial.println(" cm1" );
  Serial.print(distancia2); // CM or INC
  Serial.println(" cm2" );
  
  if(distancia>50)
  {
    digitalWrite(sonido, HIGH);
    digitalWrite(13, LOW);
  }
  if((distancia<50)&&(distancia>25))
  {
    digitalWrite(sonido, LOW);
    delay(200);
    digitalWrite(sonido, HIGH);
    delay(500);
  }
  if((distancia<25)&&(distancia>10))
  {
    digitalWrite(sonido, LOW);
    delay(200);
    digitalWrite(sonido, HIGH);
    delay(200);
  } 
  if(distancia<10)
  {
    digitalWrite(13, HIGH);
  } 

  if(distancia2>50)
  {
    digitalWrite(sonido, HIGH);
    digitalWrite(13, LOW);
  }
  if((distancia2<50)&&(distancia2>25))
  {
    digitalWrite(sonido, LOW);
    delay(200);
    digitalWrite(sonido, HIGH);
    delay(500);
  }
  if((distancia2<25)&&(distancia2>10))
  {
    digitalWrite(sonido, LOW);
    delay(200);
    digitalWrite(sonido, HIGH);
    delay(200);
  } 
  if(distancia2<10)
  {
    digitalWrite(13, HIGH);
  } 
  delay(100);
}
