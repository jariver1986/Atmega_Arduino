#include <Ultrasonic.h>
Ultrasonic ultrasonic(2,3);//Trig,Echo
int distancia=100;
int led = 4;
int alarma = 5;
int led2 = 6;
int contador=0;
int dato=0;

void setup()
{
    Serial.begin(115200);   
    pinMode(8, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
}

void loop()
{
    distancia = ultrasonic.read();
    delay(50);
    Serial.println("Distancia= "+String(distancia));
    //delay(1000);
    
    if(distancia<=5)
    {
      Serial.println("Led verde");
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      delay(500);
      contador++;
      
    }
    if (distancia>5)
    {
      Serial.println("Led rojo");
      contador=0;
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      delay(200);
    }   

    if((contador>=3)&&(contador<=7))
    {
      digitalWrite(10, HIGH);
      delay(200);
      digitalWrite(10, LOW);
      delay(200);
      
    }
    
      

    
    if (Serial.available() > 0) 
    {
      dato = Serial.read();
      if(dato=='1')
      {
          Serial.println("Alarma Activada");
          digitalWrite(10, HIGH);
          delay(200);
          digitalWrite(10, LOW);
          delay(100);
      }
      if(dato=='2')
      {
          digitalWrite(8, HIGH);
          Serial.println("Led Encendido");
          delay(1000);
      }
      if(dato=='3')
      {
          digitalWrite(8, LOW);
          Serial.println("Led apagado");
          delay(1000);
      }
      if(dato=='4')
      {
          digitalWrite(9, HIGH);
          Serial.println("Led Encendido");
          delay(1000);
      }
      if(dato=='5')
      {
          digitalWrite(9, LOW);
          Serial.println("Led apagado");
          delay(1000);
      }
      dato=0;
    }
}
