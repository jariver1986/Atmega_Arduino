#include <Ultrasonic.h>

#include<SimpleDHT.h>  //;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // RX, TX 
Ultrasonic ultrasonic(12, 13);
SimpleDHT11 temp;
byte T=0;
byte H=0;

int dato=0;
int distancia=10;
int alerta=0;
int alerta2=0;
int alerta3=0;
int contador=0;
int centinela=0;
int centinela2=0;
void setup()
{
    Serial.begin(9600);   
    mySerial.begin(9600);
    pinMode(4,OUTPUT);//Luz
    pinMode(5,OUTPUT);//Luz
    pinMode(6,OUTPUT);//Luz
    pinMode(8,OUTPUT);//Luz
    pinMode(10,OUTPUT);//Alarma
    pinMode(12,OUTPUT);//Alarma
    
    digitalWrite(4, LOW); //LUZ
    digitalWrite(5, LOW); //LUZ
    digitalWrite(6, LOW); //LUZ
    digitalWrite(8, LOW); //LUZ
    digitalWrite(10, LOW); //ALARMA
    digitalWrite(12, LOW); //ALARMA
    
    // pin 11 sensor Temperatura  DHT11   
}

void loop()
{
    distancia = ultrasonic.read();
    delay(50);
    
    if (Serial.available()>0)
    {
      dato=Serial.read();
      if(dato=='1'){alerta3=1;}// Alarma encendida
      if(dato=='2'){alerta3=0;}// Alarma apagada
      if(dato=='3'){digitalWrite(4, HIGH); }
      if(dato=='4'){digitalWrite(4, LOW); }
      if(dato=='5'){digitalWrite(5, HIGH); }
      if(dato=='6'){digitalWrite(5, LOW); }
      if(dato=='7'){digitalWrite(6, HIGH); }
      if(dato=='8'){digitalWrite(6, LOW); }
      if(dato=='9'){digitalWrite(8, HIGH); }
      if(dato=='A'){digitalWrite(8, LOW); }
      if(dato=='B'){digitalWrite(12, HIGH); }
      if(dato=='C'){digitalWrite(12, LOW); }
      dato=0;
    }

    if (mySerial.available()>0)
    {
      Serial.println(mySerial.readStringUntil('#'));
    }
    
    if(distancia<5)
    {
      alerta=1;
      centinela=1;
    }
    else
    {
      alerta=0;
    }

    if((alerta==1)||(alerta2==1)||(alerta3==1))
    {
      digitalWrite(10,HIGH);
      delay(200); 
      digitalWrite(10,LOW); 
      delay(200); 
      digitalWrite(10,HIGH);
      delay(200); 
      digitalWrite(10,LOW); 
      delay(200); 
    }
    
    //contador=contador+1;
    /*if(contador>80)
    {
      Serial.println(String(T) + "@ " + String(H)+ ";_" );
      delay(1000);
      

      delay(50);
      contador=0;

    }*/
}


        
     
