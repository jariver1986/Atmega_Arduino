#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>
// Declaramos un RTC DS3231
//Las variables utilizadas para la utilizacion del teclado 
const byte ROWS = 4;
const byte COLS = 4;
int validacion=0;
int clave=0;
//Teclado
char keys[ROWS][COLS] = 
{
 {'1','2','3','A'},
 {'4','5','6','E'},
 {'7','8','9','I'},
 {'*','0','U','O'}
};
//Ubicación de pines para la conexion arduino y teclado
byte rowPins[ROWS] = {9,8,7,6}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {5,4,3,2}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
RTC_DS1307 rtc;
int option=0;
int bomba1=10;
int valvula1=11;
int valvula2=12;
int sensor=0;
void setup () 
{
    pinMode(bomba1, OUTPUT); 
    
    pinMode(valvula1, OUTPUT); 
    pinMode(valvula2, OUTPUT); 
    Serial.begin(9600);
    
    digitalWrite(bomba1, HIGH);
    digitalWrite(valvula1, HIGH);
    digitalWrite(valvula2, HIGH);
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
void loop () 
{


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
      Serial.print(" BOMBA ENCENDIDA");
      digitalWrite(bomba1, LOW);
      option=0;
    }
    if(option=='2') 
    {
      Serial.print(" BOMBA APAGADA");
      digitalWrite(bomba1, HIGH);
      option=0;
    }
     if(option=='3') 
    {
      Serial.print(" HUMEDAD = ");
      sensor= (analogRead(0)*100)/1000;
      Serial.print(sensor);
      option=0;
    }
  
////////////////////////////////////////////
    if(option=='5') 
    {
      Serial.print(" VALVULA 1 ACTIVADA");
      digitalWrite(valvula1, LOW);
      option=0;
    }
    if(option=='6') 
    {
      Serial.print(" VALVULA 1 DESACTIVADA");
      digitalWrite(valvula1, HIGH);
      option=0;
    }
     if(option=='7') 
    {
      Serial.print(" VALVULA 2 ACTIVADA");
      digitalWrite(valvula2, LOW);
      option=0;
    }
    if(option=='8') 
    {
      Serial.print(" VALVULA 2 DESACTIVADA");
      digitalWrite(valvula2, HIGH);
      option=0;
    }
    Serial.println();
    delay(200);
  }

//funcion que detecta una tecla presionada
  char key = keypad.getKey();
/////////////////////////////////////////
if(key) 
  {
    switch (key)
    {     
        case '1':                            //Cuando key "1" es oprimida...          
          
          Serial.println("Bomba1 ON");              //El monitor serial se escribe 1 
          digitalWrite(bomba1, LOW);             //El sonido se enciende
    }
  }
 if(key) 
  {
    switch (key)
    {     
        case '2':                            //Cuando key "1" es oprimida...          
          
          Serial.println("Bomba1 OFF");              //El monitor serial se escribe 1 
          digitalWrite(bomba1, HIGH);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '3':                            //Cuando key "1" es oprimida...          
          
          Serial.println("Valvula1 ON");              //El monitor serial se escribe 1 
          digitalWrite(valvula1, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '4':                            //Cuando key "1" es oprimida...          
          
         Serial.println("Valvula1 OFF");              //El monitor serial se escribe 1 
          digitalWrite(valvula1, HIGH);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '5':                            //Cuando key "1" es oprimida...          
          
          Serial.println("Valvula2 ON");              //El monitor serial se escribe 1 
          digitalWrite(valvula2, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '6':                            //Cuando key "1" es oprimida...          
          
          Serial.println("Valvula2 OFF");              //El monitor serial se escribe 1 
          digitalWrite(valvula2, HIGH);             //El sonido se enciende
    }
  }
  
}
