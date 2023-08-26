#include <EEPROM.h>

String dato1,dato2,dato3;
void setup() {
  Serial.begin(115200);
  Serial.println("Menu");
  Serial.println("Ingrese campos ____#____#____#.");
  
}

void loop() 
{
  
  if (Serial.available() > 0) 
  {
     dato1 = Serial.readStringUntil('#');
     dato2 = Serial.readStringUntil('#');
     dato3 = Serial.readStringUntil('.');
     Serial.println("Campos ingresados");
     Serial.println(dato1);
     Serial.println(dato2);
     
  }
}
