#include <Wire.h>
#include "RTClib.h"
// Declaramos un RTC DS3231
RTC_DS1307 rtc;
void setup () {
Serial.begin(9600);
delay(3000);
// Comprobamos si tenemos el RTC conectado
if (! rtc.begin()) {
Serial.println("No hay un módulo RTC");
while (1);
}
// Ponemos en hora, solo la primera vez, luego comentar y volver a cargar.
// Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
void loop () {

if (Serial1.available()>0)
  {
    //leemos la opcion enviada
    option=Serial1.read();
    if(option=='1') 
    {
      digitalWrite(out1, HIGH);
      digitalWrite(out2, LOW);
      //Serial.println("adelante");
      delay(1000);
      digitalWrite(out1, LOW);
      digitalWrite(out2, LOW);
      option=0;
    }
    
DateTime now = rtc.now();
Serial.print(now.day());
Serial.print('/');
Serial.print(now.month());
Serial.print('/');
Serial.print(now.year());
Serial.print(" ");
Serial.print(now.hour());
Serial.print(':');
Serial.print(now.minute());
Serial.print(':');
Serial.print(now.second());
Serial.println();
delay(200);
  }
}
