//=====================================Servomotor
#include <Servo.h>
Servo pulgar;
Servo indice;
Servo medio;
Servo anular;
Servo menique;
int abierto = 10;
int cerrado = 90;
int cerrado2 = 90;

int rx=0;

//=====================================Teclado
#include <Keypad.h>
const byte rowsCount = 3;
const byte columsCount = 3;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3' },
   { '4','5','6' },
   { '7','8','9' }
};
 
const byte rowPins[rowsCount] = {  12, 11, 8 };
const byte columnPins[columsCount] = {  7, 4, 2 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 

//============================================
void setup() 
{
  //==========================================Servomotor
  pulgar.attach(3);
  indice.attach(5);
  medio.attach(6);
  anular.attach(9);
  menique.attach(10);
  
  Serial.begin(115200);
  pulgar.write(abierto);
  indice.write(abierto);
  medio.write(abierto);
  anular.write(abierto);
  menique.write(abierto);

  //==========================================teclado
}
void loop() 
{
  //Recepcion de datos seriales 1 2 3 4 o 5
  if (Serial.available() >0) 
  {
      rx = Serial.read();
      if(rx == '1'){pulgar.write(cerrado2);}
      if(rx == '2'){indice.write(cerrado2);}
      if(rx == '3'){medio.write(cerrado2);}
      if(rx == '4'){anular.write(cerrado2);}
      if(rx == '5'){menique.write(cerrado2);}
      delay(1000);
      pulgar.write(abierto); 
      indice.write(abierto);
      anular.write(abierto);
      medio.write(abierto); 
      menique.write(abierto);
      rx=0;
  }
  //lectura de teclado
  char key = keypad.getKey();
  if (key) 
  {
      Serial.println(key);
      if(key=='1'){pulgar.write(cerrado);}
      if(key=='2'){indice.write(cerrado);}
      if(key=='3'){medio.write(cerrado);}
      if(key=='4'){anular.write(cerrado);}
      if(key=='5'){menique.write(cerrado);}
      delay(1000);
      pulgar.write(abierto); 
      indice.write(abierto);
      anular.write(abierto);
      medio.write(abierto); 
      menique.write(abierto);
      key=0;
  }
  delay(100);
}
