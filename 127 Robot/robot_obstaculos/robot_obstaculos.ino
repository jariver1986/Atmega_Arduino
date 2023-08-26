#include <Ultrasonic.h>
Ultrasonic ultrasonic(8,9);//Trig,Echo
int distancia=100;
// MOTOR 1
int IN1 = 2;
int IN2 = 7;
int ENA = 6;
// MOTOR 2
int IN3 = 4;
int IN4 = 3;
int ENB = 5;
int dato=0;

void setup()
{
    Serial.begin(115200);   
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);
    parar();
}
void avanza(){
 // MOTOR 1 
  analogWrite (ENA, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // MOTOR 2
  analogWrite(ENB, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void parar(){
 // MOTOR 1 
  digitalWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  digitalWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void derecha(){
 // MOTOR 1 
  analogWrite (ENA, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  analogWrite (ENB, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void izquierda(){
 // MOTOR 1 
  analogWrite (ENA, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // MOTOR 2
  analogWrite (ENB, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop()
{
    distancia = ultrasonic.read();
    Serial.println("Distancia= "+String(distancia));
    //delay(1000);
    
    if(distancia>15)
    {
      avanza();
    }
    else
    {
      //retrocede();
      //zquierda();
      parar();
      delay(500);
      derecha();
      delay(100);
    }   
    
    /*if (Serial.available() > 0) 
    {
      dato = Serial.read();
      if(dato=='1')
      {
          avanza();
          Serial.println("avanza");
      }
      if(dato=='2')
      {
          derecha();
          Serial.println("derecha");
      }
      if(dato=='3')
      {
          parar();
          Serial.println("parar");
      }
      dato=0;
    }*/
    
}


        
     
