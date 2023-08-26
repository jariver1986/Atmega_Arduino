#include <Servo.h>
#include <Keypad.h>   

     byte fila[] = {9, 8, 7, 6};     
     byte columna[] = { 5, 4, 3, 2};          
     
     char teclas [ 4][ 4 ] =
          {
              {'1','2','3','A'},
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
     Keypad teclado = Keypad(makeKeymap(teclas), fila, columna, 4, 4);

Servo control1;
int contador = 0;
int centinela=0;
int lazo =0;
void setup() 
{
    control1.attach(10);
    control1.write(0);
    
}

void loop() 
{
  char pulsacion = teclado.getKey() ;
  if (pulsacion != 0)              
    Serial.print(pulsacion);   
    
  if (pulsacion == '1')              
  {
      lazo=1;
  }
  if (pulsacion == '2')              
  {
      lazo=0;
  }

  if (pulsacion == 'A')              
  {
      control1.write(0);
  }
  if (pulsacion == 'B')              
  {
      control1.write(90);
  }
  
  
  if (lazo == 1)              
  {
    centinela++;
    if (centinela<85 )
    {
      control1.write(contador);
      delay(10);
      contador++;
    }
    if (centinela>85 )
    {
      control1.write(contador);
      delay(10);
      contador--;
    }
    if(centinela>170)
    {
      centinela=0;
      contador=0;
    }
  }
      
}

//////////////////////////////////////////////////////////////////
/*
 * #include <Servo.h>
Servo control1;
int contador = 0;
int centinela=0;
void setup() 
{
    control1.attach(9);
}

void loop() 
{
  centinela++;
  if (centinela<85 )
  {
    control1.write(contador);
    delay(10);
    contador++;
  }
  if (centinela>85 )
  {
    control1.write(contador);
    delay(10);
    contador--;
  }
  if(centinela>170)
  {
    centinela=0;
    contador=0;
  }
      
}
 */ 
 
 
