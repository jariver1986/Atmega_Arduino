#include <Ultrasonic.h>
Ultrasonic ultrasonic(2,3);//Trig,Echo
int distancia=100;
int led = 4;
int dato=0;
int centinela=0;
int val=0;
int contador=0;
void semaforo1(){
  digitalWrite(7, LOW); //R
  digitalWrite(6, LOW); //A
  digitalWrite(5, HIGH);//V

  digitalWrite(10,HIGH);//R
  digitalWrite(9, LOW); //A
  digitalWrite(8, LOW); //V
  }
void procesoA(){
  digitalWrite(7, LOW); //R
  digitalWrite(6, HIGH); //A
  digitalWrite(5, LOW);//V

  digitalWrite(10,HIGH);//R
  digitalWrite(9, LOW); //A
  digitalWrite(8, LOW); //V
  }
void semaforo2(){
  digitalWrite(7, HIGH);//R
  digitalWrite(6, LOW); //A
  digitalWrite(5, LOW); //V

  digitalWrite(10,LOW);  //R
  digitalWrite(9, LOW);  //A
  digitalWrite(8, HIGH); //V
  }
void procesoB(){
  digitalWrite(7, HIGH); //R
  digitalWrite(6, LOW);  //A
  digitalWrite(5, LOW);  //V

  digitalWrite(10,LOW);  //R
  digitalWrite(9, HIGH); //A
  digitalWrite(8, LOW);  //V
  }
  void encender(){
  digitalWrite(7, HIGH); //R
  digitalWrite(6, HIGH); //A
  digitalWrite(5, HIGH);//V

  digitalWrite(10,HIGH);//R
  digitalWrite(9, HIGH); //A
  digitalWrite(8, HIGH); //V
  }
  void apagar(){
  digitalWrite(7, LOW); //R
  digitalWrite(6, LOW); //A
  digitalWrite(5, LOW);//V

  digitalWrite(10,LOW);//R
  digitalWrite(9, LOW); //A
  digitalWrite(8, LOW); //V
  }
void setup()
{
  Serial.begin(115200);   
  pinMode(12, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(12, LOW); //R

  apagar();
  delay(500);
  encender();
  delay(500);
  apagar();
  delay(500);
  encender();
  delay(500);
  
  semaforo1();
  delay(500);
  procesoA();
  delay(500);
  semaforo2();
  delay(500);
  procesoB();
  delay(500);
  semaforo1();
}

void loop()
{
    distancia = ultrasonic.read();
    delay(50);
    Serial.println("Distancia= "+String(distancia));
    //delay(1000);
     delay(50);
    if (digitalRead(12) == HIGH) 
    {
      contador=9;
    }
     delay(50);
    if((distancia<=5)||(val==HIGH))
    {
      contador=10;
    }
    if (distancia>5)
    {
      contador++;
    }   
    delay(1000);
    
    if(contador==10)
    {
      procesoA();
      delay(1000);  
      semaforo2();
    }
    if(contador==20)
    {
      procesoB();
      delay(1000);  
      semaforo1();
    }
    if(contador==21)
    {
        contador=0;
    }
    
    
    
    
    
    
    if (Serial.available() > 0) 
    {
      dato = Serial.read();
      if(dato=='1')
      {
          semaforo1();
          delay(100);
      }
      if(dato=='2')
      {
          procesoA();
          delay(100);
      }
      if(dato=='3')
      {
          semaforo2();
          delay(100);
      }
      if(dato=='4')
      {
          procesoB();
          delay(100);
      }
      if(dato=='5')
      {
          contador=9;
          delay(100);
      }
      dato=0;
    }
}
