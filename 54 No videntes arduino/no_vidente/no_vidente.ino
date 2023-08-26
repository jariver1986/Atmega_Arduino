#include <Ultrasonic.h>
//variables a utlizar
int option;
int distancia=0;
Ultrasonic ultrasonic(6,7,23200);// (Trig PIN,Echo PIN, TIMEOUT)
//TIMEOUT = (CENTIMETROS)*(58)
//Inicio
void setup()
{
  //pin de sonido de alerta
  pinMode(13,OUTPUT);
  Serial.begin(9600);      
  digitalWrite(13,HIGH);
}

void loop()
{
  //pregunta por datos recibidos
    if (Serial.available()>0)
    {
      option=Serial.read();
    }
     if(option=='1') 
    {
      //envia dato de distancia por serial al telefono
       Serial.println(ultrasonic.Ranging(CM));
       option=0;
    }
    //detecta obtaculo y si es menor distancia que 1 metro envia notificacion
    distancia=ultrasonic.Ranging(CM);
    if (distancia<100)
    {
      //emite sonido de alerta
      Serial.println(distancia);
      digitalWrite(13,HIGH);
      delay(200);
      digitalWrite(13,LOW);
      delay(200);
      digitalWrite(13,HIGH);
      delay(200);
      digitalWrite(13,LOW);
      delay(200);
      digitalWrite(13,HIGH);
    }
    
    delay(300);
    

    
  }




