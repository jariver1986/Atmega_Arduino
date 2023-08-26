#include <Servo.h>
int led = 13;//Inicicializacion de variable
int sensor1 =0;
int sensor2 =0;
int limite1=75;
int centinela=0;
int contador=20;
int contador2=0;
Servo miServo1;//Inicicializacion de sewrvomotor
Servo miServo2;//Inicicializacion de sewrvomotor

void setup()
{  
  Serial.begin(9600);
  miServo1.attach(3);//asigncion de pines de servomotor
  miServo2.attach(5);//asigncion de pines de servomotor
  miServo1.write(contador);  //Altura
  miServo2.write(contador2); //giro en el eje
  delay(2000);  
}
 

void loop()
{
    sensor1 = analogRead(A0);
    while (sensor1>limite1)
    {
      sensor1 = analogRead(A0);
      contador=contador+10;
      if (contador>160)//limitantre de elevacion
      {
          contador=160;  //asignacion de angulo de giro
      }
      miServo1.write(contador);//ejecucion de giro
      Serial.println("A"+String(sensor1)+"B");
      delay(400);
    }
    contador=contador-10;
      if (contador<20)//limitantre de elevacion
      {
          contador=20;  //asignacion de angulo de giro
      } 
    Serial.println("A"+String(sensor1)+"B");
    miServo1.write(contador);//ejecucion de giro
    delay(200);
}
//+++++++++++++FIN+++++++++++++++++++++++++++++
