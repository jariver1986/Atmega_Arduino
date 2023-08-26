#include <Servo.h>
int led = 13;//Inicicializacion de variable
int sensor1 =0;
int sensor2 =0;
int limite1=115;
int centinela=0;
int contador=0;
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
    //Serial.println(sensor1);
    if (sensor1>limite1)
    {
      contador=contador+30;
      if (contador>120)//limitantre de elevacion
      {
          contador=120;  //asignacion de angulo de giro
      } 
      miServo1.write(contador);//ejecucion de giro
      //Serial.println(contador);
    }
    delay(400);

    sensor2 = analogRead(A1);
    Serial.println(sensor2);
    if (sensor2>limite1)
    {
      contador=contador-30;
      if (contador<0)//limitantre de elevacion
      {
          contador=0;  //asignacion de angulo de giro
      } 
      miServo1.write(contador);//ejecucion de giro
      //Serial.println(contador);
    }
    delay(400);
    Serial.println();

  
    
}
//+++++++++++++FIN+++++++++++++++++++++++++++++
