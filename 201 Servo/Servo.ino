#include <Servo.h>

Servo Pruebo2 ; 
int secuencia=0;
void setup() 
{
 
  Pruebo2.attach(3);
  
 }
void loop() 
{  
  //El incremento de la variable pausada a 50ms pueden probar con 100, 150 segun la velocidad requerida,
  Pruebo2.write(secuencia);
  delay(50);
  secuencia++;


  //maximo 90 grados y vuelve a cero
  if(secuencia>90)
  {
    secuencia=0;  
    Pruebo2.write(secuencia);
    delay(2000);
  }
  
  
}
/*
void loop() {  
  Pruebo2.write(0);
  delay(2000);

  Pruebo2.write(90);
  delay(2000);

  Pruebo2.write(180);
  delay(2000);

  Pruebo2.write(90);
  delay(2000);

  
}*/
