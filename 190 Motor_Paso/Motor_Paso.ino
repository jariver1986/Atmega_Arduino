//Modo secuencia

////Librerias
#include <Stepper.h>
#include <Servo.h>

//Variables
int steps = 128;
int motSpeed =10;
int dt = 1500;
int contador=0;

////Objetos
Servo Pruebo2 ;
Stepper myStepper(steps,8,10,9,11);

//Configuracion inicial
void setup() 
{
  //////////Servomotor
  Pruebo2.attach(3);

  //////////Motor Paso
  myStepper.setSpeed(motSpeed);

}

////Cuerpo del proyecto
void loop() 
{
  contador++; //incremento en 1 la variable
  ///////////////////////Servomotor
  if(contador==2)
    Pruebo2.write(0);

  if(contador==4)
    Pruebo2.write(90);

  if(contador==6)
    Pruebo2.write(180);

  if(contador==8)
    Pruebo2.write(90);
    
  /////////////////////////Motor de Paso
  if (contador==2)
    myStepper.step(steps);
  if (contador==4)
    myStepper.step(-steps);  
  if (contador==6)
    myStepper.step(steps);
  if (contador==8)
    myStepper.step(-steps); 

  /////////////////////////reinicio de proceso
  if (contador==10)
    contador = 2;
  
  //////////////////////////Retardo general para el sistema
  delay(1000);
}
