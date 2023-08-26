//rojo E+
//negro E-
//verde A-
//blanco A+

int out1 = 8;
int out2 = 9;

int centinela=0;
int option;

#include "HX711.h"
#define DOUT  A1
#define CLK  A0

//+++++++++++++++++++++PARAMETROS++++++++++++++++++++++++++++++++++++++
int tiempo=600;
int masa_programada=10;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

HX711 balanza(DOUT, CLK);

void setup() {
  Serial.begin(9600);
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  balanza.set_scale(); //La escala por defecto es 1
  balanza.tare(20);  //El peso actual es considerado Tara.
  Serial.println("Coloque un peso conocido:");
  pinMode(out1, OUTPUT); //Motor 1
  pinMode(out2, OUTPUT); //Motor 2
  digitalWrite(out1, LOW);//salidas digitsles
  digitalWrite(out2, LOW);//salidas digitsles
   digitalWrite(out1, LOW);//salidas digitsles
   digitalWrite(out2, HIGH);//salidas digitsles
   delay(150);
   digitalWrite(out1, LOW);//salidas digitsles
   digitalWrite(out2, LOW);//salidas digitsles
  
}


void loop() 
{
    if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') //Funcion que controla carro para ADELANTE
    {
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, HIGH);//salidas digitsles
      delay(100);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      option=0;
    }
    if(option=='2') //Funcion que controla carro para ADELANTE
    {
      digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      delay(100);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      option=0;
    }
  }
  Serial.print("Valor de lectura:  ");
  Serial.println(balanza.get_value(10),0);

  if ((balanza.get_value(10)<-1000000)&&(centinela==0))
  {
      digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      delay(200);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      centinela=1;
  }
  
  delay(200);
  
  
}
