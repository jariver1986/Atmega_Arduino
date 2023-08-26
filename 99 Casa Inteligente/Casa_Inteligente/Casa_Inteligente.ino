#include <Ultrasonic.h>
#include<Servo.h>
#include<SimpleDHT.h>  //;

Ultrasonic sensor(8,9,23200);
Ultrasonic sensor2(10,11,23200);
Servo control1;
SimpleDHT11 temp;
byte T=0;
byte H=0;

int dato=0;
int distancia=0;
int distancia2=0;
int alerta=0;
int alerta2=0;
int alerta3=0;
int contador=0;
int centinela=0;
int centinela2=0;
void setup()
{
    Serial.begin(9600);   
    pinMode(2,OUTPUT);//Luz
    pinMode(3,OUTPUT);//Luz
    pinMode(4,OUTPUT);//Luz
    pinMode(5,OUTPUT);//Luz
    pinMode(6,OUTPUT);//Alarma
    pinMode(12,OUTPUT);//Luz

    
    digitalWrite(2, LOW); //LUZ
    digitalWrite(3, LOW); //LUZ
    digitalWrite(4, LOW); //LUZ
    digitalWrite(5, LOW); //LUZ
    digitalWrite(6, LOW); //ALARMA
     digitalWrite(12, LOW); //LUZ
    // pin9 pin10 sensor distancia
    // pin 7 sensor Temperatura    
}

void loop()
{
    distancia=sensor.Ranging(CM);
    delay(50);
    distancia2=sensor2.Ranging(CM);
    delay(50);

    
    if (Serial.available()>0)
    {
      dato=Serial.read();
      if(dato=='1'){alerta3=1;}
      if(dato=='2'){alerta3=0;}
      if(dato=='3'){digitalWrite(2, HIGH); }
      if(dato=='4'){digitalWrite(2, LOW); }
      if(dato=='5'){digitalWrite(3, HIGH); }
      if(dato=='6'){digitalWrite(3, LOW); }
      if(dato=='7'){digitalWrite(4, HIGH); }
      if(dato=='8'){digitalWrite(4, LOW); }
      if(dato=='9'){digitalWrite(5, HIGH); }
      if(dato=='A'){digitalWrite(5, LOW); }
      if(dato=='B'){digitalWrite(12, HIGH); }
      if(dato=='C'){digitalWrite(12, LOW); }
      dato=0;
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
    if(distancia2<5)
    {
      alerta2=1;
      centinela2=1;
    }
    else
    {
      alerta2=0;
    }



    if((alerta==1)||(alerta2==1)||(alerta3==1))
    {
      digitalWrite(6,HIGH);
      delay(200); 
      digitalWrite(6,LOW); 
      delay(200); 
    }
    contador=contador+1;
    if(contador>80)
    {
      temp.read(7,&T,&H,NULL);
      Serial.println("__@"+String(T)+";_");
      delay(1000);
      if(centinela==1)
      {
        Serial.println("_AA@"+String(T)+";_");  
        delay(1000);
        centinela=0;
      }
      if(centinela2==1)
      {
        Serial.println("_BB@"+String(T)+";_");  
        delay(1000);
        centinela2=0;
      }
      
      delay(50);
      contador=0;
      //Serial.println(distancia2);
    }
}


        
     
