#include <Ultrasonic.h>
int sonido=2;

int distancia=0;

Ultrasonic ultrasonic(6,7,23200); // (Trig PIN,Echo PIN, TIMEOUT)
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
  if(distancia<50)
  {
    digitalWrite(sonido, HIGH);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(sonido, LOW);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(sonido, HIGH);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(sonido, LOW);
    digitalWrite(13, LOW);
    delay(100);
    Serial.print(" Distancia. " );
    Serial.print(distancia); // CM or INC
    Serial.println(" centimetros" );
    delay(5000);
  }
  delay(1000);
}
