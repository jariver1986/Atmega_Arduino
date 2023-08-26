#include <Wire.h>
#include "RTClib.h"
// Declaramos un RTC DS3231
RTC_DS1307 rtc;
int option=0;
int bomba1=2;
int bomba2=3;
int valvula1=3;
int valvula2=4;
void setup () 
{
    pinMode(bomba1, OUTPUT); 
    pinMode(bomba2, OUTPUT); 
    pinMode(valvula1, OUTPUT); 
    pinMode(valvula2, OUTPUT); 
    Serial.begin(9600);
    delay(3000);
    // Comprobamos si tenemos el RTC conectado
    if (! rtc.begin()) 
    {
    Serial.println("No hay un módulo RTC");
    while (1);
    }
    // Ponemos en hora, solo la primera vez, luego comentar y volver a cargar.
    // Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
void loop () {

if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
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
    
    if(option=='1') 
    {
      Serial.print(" BOMBA 1 ENCENDIDA");
      option=0;
    }
    if(option=='2') 
    {
      Serial.print(" BOMBA 1 APAGADA");
      option=0;
    }
     if(option=='3') 
    {
      Serial.print(" BOMBA 2 ENCENDIDA");
      option=0;
    }
    if(option=='4') 
    {
      Serial.print(" BOMBA 2 APAGADA");
      option=0;
    }
////////////////////////////////////////////
    if(option=='5') 
    {
      Serial.print(" VALVULA 1 ACTIVADA");
      option=0;
    }
    if(option=='6') 
    {
      Serial.print(" VALVULA 1 DESACTIVADA");
      option=0;
    }
     if(option=='7') 
    {
      Serial.print(" VALVULA 2 ACTIVADA");
      option=0;
    }
    if(option=='8') 
    {
      Serial.print(" VALVULA 2 DESACTIVADA");
      option=0;
    }
    Serial.println();
    delay(200);
  }
}
