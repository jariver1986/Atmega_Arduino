	
#include <Ultrasonic.h>
Ultrasonic ultrasonic(10,11,3000); // (Trig PIN,Echo PIN, TIMEOUT)


int option;
int piston1 = 13;
int piston2 = 12;
int piston3 = 8;
int piston4 = 7;
int piston5 = 4;
int piston6 = 2;
int piston7 = 3;
int piston8 = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(piston1, OUTPUT); 
  pinMode(piston2, OUTPUT); 
  pinMode(piston3, OUTPUT); 
  pinMode(piston4, OUTPUT); 
  pinMode(piston5, OUTPUT); 
  pinMode(piston6, OUTPUT); 
  pinMode(piston7, OUTPUT); 
  pinMode(piston8, OUTPUT); 
  digitalWrite(piston1, LOW);
  digitalWrite(piston2, LOW);
  digitalWrite(piston3, LOW);
  digitalWrite(piston4, LOW);
  digitalWrite(piston5, LOW);
  digitalWrite(piston6, LOW);
  digitalWrite(piston7, LOW);
  digitalWrite(piston8, LOW);
}
void dosis(int d1,int d2,int d3,int d4,int d5,int d6, int d7,int d8)
{
  
      digitalWrite(piston1, HIGH); delay(d1); digitalWrite(piston1, LOW);
      delay(200);
      digitalWrite(piston2, HIGH); delay(d2); digitalWrite(piston2, LOW);
      delay(200);
      digitalWrite(piston3, HIGH); delay(d3); digitalWrite(piston3, LOW);
      delay(200);
      digitalWrite(piston4, HIGH); delay(d4); digitalWrite(piston4, LOW);
      delay(200);
      digitalWrite(piston5, HIGH); delay(d5); digitalWrite(piston5, LOW);
      delay(200);
      digitalWrite(piston6, HIGH); delay(d6); digitalWrite(piston6, LOW);
      delay(200);
      digitalWrite(piston7, HIGH); delay(d7); digitalWrite(piston7, LOW);
      delay(200);
      digitalWrite(piston8, HIGH); delay(d8); digitalWrite(piston8, LOW);
      Serial.println("R");
}
void loop()
{
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();

    if ((ultrasonic.Ranging(CM)) < 30)
    {
            if(option=='a') //cuba libre
            {
              dosis(0,0,4000,0,0,3000,2000,0);
            }
            if(option=='b') //Destornillador
            {
             dosis(4000,0,0,3000,0,0,1000,0);
            }
            if(option=='c') //Cuba gooding jr
            {
               dosis(3000,0,3000,0,0,3000,2000,0);
            }
            if(option=='d') //Sexo en la Playa
            {
               dosis(3000,0,0,3000,0,3000,1000,0);
            }
            if(option=='e') //Infarto
            {
               dosis(0,0,0,4000,0,0,4000,0);
            }
            if(option=='f') //Coco Loco
            {
               dosis(0,0,0,4000,0,4000,1000,0);
            }
            if(option=='g') // Roncola
            {
               dosis(0,0,4000,0,0,4000,0,0);
            } 
            ///////////////////////////
            if(option=='1') // Roncola
            {
               dosis(1000,0,0,0,0,0,0,0);
            } 
            if(option=='2') // Roncola
            {
               dosis(0,0,1000,0,0,0,0,0);
            } 
            if(option=='3') // Roncola
            {
               dosis(0,0,0,1000,0,0,0,0);
            } 
            if(option=='4') // Roncola
            {
               dosis(0,0,0,0,0,1000,0,0);
            } 
            if(option=='5') // Roncola
            {
               dosis(0,0,0,0,0,0,1000,0);
            } 
    }//if
  }
  option=0;
}
