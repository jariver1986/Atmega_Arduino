#include <SPI.h>
#include <Wire.h>
#include "HX711.h"
#define DOUT  3
#define CLK  2

//+++++++++++++++++++++PARAMETROS++++++++++++++++++++++++++++++++++++++
int tiempo=200;
int masa_programada=10;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

HX711 scale(DOUT, CLK);
float calibration_factor = -11980;
int relay = 12;
int centinela=0;
int option;
int out1 = 8;
int out2 = 9;
void setup() 
{
  Serial.begin(4800);
  pinMode(relay, OUTPUT); 
  pinMode(out1, OUTPUT); //Motor 1
  pinMode(out2, OUTPUT); //Motor 2
  digitalWrite(out1, LOW);//salidas digitsles
  digitalWrite(out2, LOW);//salidas digitsles
  digitalWrite(relay, HIGH);//salidas digitsles  
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  //Initialize with the I2C addr. Use 0x3C if board jumper is 0x78, and 0x3D if board jumper is 0x7A
   Serial.println("CLEARDATA");
   Serial.println("LABEL,Date,Time,Masa[Lbrs]");
   digitalWrite(out1, LOW);//salidas digitsles
   digitalWrite(out2, HIGH);//salidas digitsles
   delay(tiempo);
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

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  //Serial.println(scale.get_units(1), 1);
  displayValue(scale.get_units(20)  );
  Serial.print( (String) "DATA,DATE,TIME," );
  Serial.println(9.6);
  //Serial.println((scale.get_units(20))*(-1) );
  //delay(100);
}
void displayValue(float val)
{
  //Serial.print("Masa[Lbrs]: ");
 //Serial.println(scale.get_units(20) );
  if((val<-masa_programada)&&(centinela==0))
  {
      digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      delay(tiempo);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      centinela=1;
   }
  delay(1000);
}
