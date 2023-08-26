#include <hcsr04.h>
#include <Servo.h> 

#define TRIG_PIN 12
#define ECHO_PIN 13
Servo myServo;
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
int distancia =0;
int mi1 = 8; 
int mi2 = 9; 
int md1 = 6; 
int md2 = 7;



void setup()
{
    Serial.begin(115200);
    pinMode(mi1, OUTPUT); 
    pinMode(mi2, OUTPUT);
    pinMode(md1, OUTPUT); 
    pinMode(md2, OUTPUT);  
    myServo.attach(10);
    myServo.write(115);//mirar adelante
    delay(2000); 
    myServo.write(65);//mirar a la derecha
    delay(2000);
    myServo.write(160);//mirar a la izquierda
    delay(2000);
    myServo.write(115); // mirar adelante
}

///////////////////////////////////////////////Funciones
void mirar_izquierda()
{
  myServo.write(160);
  delay(1000);
}
void mirar_derecha()
{
  myServo.write(65);
  delay(1000);
}
void mirar_frente()
{
  myServo.write(115);
  delay(1000);
}
void atras(){
  digitalWrite(mi1, HIGH);
  digitalWrite(mi2, LOW);
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
}
void pare(){
digitalWrite(mi1, LOW);
digitalWrite(mi2, LOW);
digitalWrite(md1, LOW);
digitalWrite(md2, LOW);
}

void adelante(){
digitalWrite(mi1, LOW);
digitalWrite(mi2, HIGH);
digitalWrite(md1, LOW);
digitalWrite(md2, HIGH);
}

void derecha(){
  digitalWrite(mi1, LOW);
  digitalWrite(mi2, HIGH);
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
}
void izquierda(){
  digitalWrite(mi1, HIGH);
  digitalWrite(mi2, LOW);
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
}
void giro(){
  digitalWrite(mi1, HIGH);
  digitalWrite(mi2, LOW);
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
}

///////////////////////////////////////////////
void loop() 
{
  if (Serial.available())
   {
      char data = Serial.read();
      if (data == '2')
      {
         mirar_frente();
      }
      if (data == '1')
      {
         mirar_izquierda();
      }
      if (data == '3')
      {
         mirar_derecha();
      }
      if (data == 'w')
      {
         adelante();
      }
      if (data == 'x')
      {
         atras;
      }
      if (data == 'a')
      {
         izquierda();
      }
      if (data == 'd')
      {
         derecha();
      }
      if (data == 's')
      {
         pare();
      }
      
      
   }
   
  distancia = hcsr04.distanceInMillimeters();
  Serial.println("Distancia = " + String(distancia));
  //Serial.println(hcsr04.ToString());
  delay(250);

  
  if (distancia > 200)
  {
    adelante();
    Serial.println("Distancia = " + String(distancia));
    Serial.println("adelante");
  }
  else
  {
    pare();
    delay(1000);
    mirar_derecha();
    delay(1000);
    distancia = hcsr04.distanceInMillimeters();
    Serial.println("Distancia = " + String(distancia));
    Serial.println("miro derecha");
    if(distancia > 200)
    {
      pare();
      delay(1000);
      derecha();
      Serial.println("giro derecha");
      delay(250);  
      pare();
      delay(1000);
      mirar_frente();
      delay(1000);
    }
    else
    {
      mirar_izquierda();
      delay(1000);
      distancia = hcsr04.distanceInMillimeters();
      Serial.println("Distancia = " + String(distancia));
      Serial.println("miro izquierda");
      if(distancia > 200)
      {
        pare();
        delay(1000);
        izquierda();  
        Serial.println("giro izquierda");
        delay(250);
        pare();
        delay(1000);
        mirar_frente();
        delay(1000);
      }
      else
      {
        mirar_frente();
        atras();
        Serial.println("giro izquierda");
        delay(1000);
        pare();
        Serial.println("paro");
        delay(1000);
        giro();
        Serial.println("giro");
        delay(500);
        pare();  
        Serial.println("FIN");
      }
    }
  }
  
}
