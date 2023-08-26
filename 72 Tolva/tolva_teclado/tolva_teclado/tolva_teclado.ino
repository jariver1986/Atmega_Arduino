#include <SPI.h>
#include <Wire.h>
#include "HX711.h"
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
{
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
byte rowPins[ROWS] = {11,10,9,8}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {7,6,5,4}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define DOUT  3
#define CLK   2
//+++++++++++++++++++++PARAMETROS++++++++++++++++++++++++++++++++++++++
int tiempo=200;
int masa_programada=2;
int parametro=12;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int out1 = 12;
int out2 = 13;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HX711 scale(DOUT, CLK);
float calibration_factor = -11980;
int centinela=0;
int option;
void setup() 
{
  Serial.begin(4800);   
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  //Initialize with the I2C addr. Use 0x3C if board jumper is 0x78, and 0x3D if board jumper is 0x7A
  pinMode(out1, OUTPUT); //Motor 1
  pinMode(out2, OUTPUT); //Motor 2
  digitalWrite(out1, LOW);//salidas digitsles
  digitalWrite(out2, LOW);//salidas digitsles
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
      Serial.println("serial 1");
      option=0;
    }
  }
  char key = keypad.getKey();
  /////////////////////////////////////////Boton A
  if(key) 
  {
    switch (key)
    {   
      case 'A':                            //Cuando key "A" es oprimida...          
      Serial.println("Boton A");   //El monitor serial escribe "ElectroCrea.com"
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, HIGH);//salidas digitsles
      delay(100);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      option=0;
      break;
    }
  }
  if(key) 
  {
    switch (key)
    {   
      case 'B':                            //Cuando key "A" es oprimida...          
      Serial.println("Boton B");   //El monitor serial escribe "ElectroCrea.com"
      digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      delay(100);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      break;
    }
  }
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  //Serial.println(scale.get_units(1), 1);
  displayValue(scale.get_units(20)  );
  delay(1000);
}
void displayValue(float val)
{ 
  Serial.print("Masa[Lbrs]: ");
  Serial.println(val+parametro);
  if((val<-masa_programada)&&(centinela==0))
  {
    digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      delay(tiempo);
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      centinela=1;
      Serial.println("Cerrado");
  }
}
