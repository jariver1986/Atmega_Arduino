#include <FreqCount.h>



/////////////////////////////////////////////////////////////////////

int S0 = 8;//pinB
int S1 = 9;//pinA
int S2 = 12;//pinE
int S3 = 11;//pinF
int Out = 5;//pinC PARA EL ARDUINO MEGA SE CAMBIA POR EL PIN 47
int LED = 13;//pinD
int unChar;
word absoluto;
word ROJO;
word VERDE;
word AZUL;
word color;


void setup()
{
Serial.begin(9600);
FreqCount.begin(10);

pinMode(LED,OUTPUT); //LED pinD
    
pinMode(S2,OUTPUT); //S2 pinE
pinMode(S3,OUTPUT); //s3 pinF
    
pinMode(Out, INPUT); //Frecuency Out pinC # 47 on Arduino Mega 2560
    
pinMode(S0,OUTPUT); //S0 pinB
pinMode(S1,OUTPUT); //S1 pinA 
}
 
void loop()
{
  if (Serial.available() >= 0) 
  {
  // escucha la llegada de nuevos datos serie:
  unChar = Serial.read();
    if (unChar == 'R') 
    {
         absoluto = (FreqCount.read()/10)*2;
         Serial.println('%lu',absoluto);
         delay(1000);
    }         
  }   
  unChar=0;
}
