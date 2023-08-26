#include <Servo.h>

//variable de recepcion de datos y cariables de control de elevacion
int option;
int led = 13;
int contador=0;
int contador2=85;
int contador3=90;
int inicio=0;

Servo miServo1;
Servo miServo2;
Servo miServo3;
Servo miServo4;


void setup()
{
 //asignacion de comunicacion de datos entre arduino y antena bt
  Serial.begin(9600);

//Asignacion de pines del servomotor
  miServo1.attach(3);
  miServo2.attach(5);
  miServo3.attach(2);
  miServo4.attach(9);


  //Posicionamiento inicial
  miServo1.write(contador);  //Altura
  miServo2.write(contador2); //giro en el eje
  miServo3.write(contador3); //giro en el eje
  
  
}


 
void loop()
{
  
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    ///////////////////////////
    if(option=='p') 
    {
       miServo1.write(180);
      delay(3000);
      miServo1.write(0);
      delay(2000);
    }
    if(option=='f') 
    {
      miServo1.write(0);
      contador=0;
    }
    
    if(option=='u') 
    {
     
      contador=contador+10;
      if (contador>180)//limitantre de elevacion
      {
          contador=180;  
      } 
      miServo1.write(contador);
      Serial.println(contador);
      
    }
    if(option=='d') 
    {
      
      contador=contador-10;
      if (contador<0)
      {
          contador=0;  
      }
      miServo1.write(contador);
      Serial.println(contador); 
    }
    if(option=='l') 
    {
     
      contador2=contador2+10;
      if (contador2>180)
      {
          contador2=180;  
      } 
      miServo2.write(contador2);
      Serial.println(contador2);
      
    }
    if(option=='r') 
    {
      
      contador2=contador2-10;
      if (contador2<0)
      {
          contador2=0;  
      }
      miServo2.write(contador2);
      Serial.println(contador2); 
    }
    if(option=='g') 
    {
     
      contador3=contador3+10;
      if (contador3>180)
      {
          contador3=180;  
      } 
      miServo3.write(contador3);
      Serial.println(contador3);
      
    }
    if(option=='b') 
    {
      
      contador3=contador3-10;
      if (contador3<0)
      {
          contador3=0;  
      }
      miServo3.write(contador3);
      Serial.println(contador3); 
    }

  }   
  
}
