#include <SPI.h>
#include <MFRC522.h>
RFID rfid(10,5);
void setup()
{
  Serial.begin(9600); //Inicializa la velocidad de Serial
  SPI.begin();  //Función que inicializa SPI
  rfid.init();      //Función  que inicializa RFID
}
void loop()
{
     if (rfid.isCard()) { //Verifica si hay una tarjeta
           if (rfid.readCardSerial()) 
           { //Funcion que lee la tarjeta
                Serial.println(" ");
                Serial.println(" ");
                Serial.println("El numero de serie de la tarjeta es  : ");
                for(int i=0; i<=4; i++){
                      if(i!=4)
                      {
                      Serial.print(rfid.serNum[i],HEX); //rfid.serNum lee el número de serie unico de la tarjeta
                      Serial.print(" ");
                      }
                      else
                      {
                        Serial.print(rfid.serNum[i],HEX);
                        Serial.print(" ");
                      }
            }
                        delay(1000);
          }
     }
    rfid.halt();
}
/*
//**********************************************************************************
//Ejemplo de como usar RFID RC522
//**********************************************************************************

#include <SPI.h>
#include <RFID.h>

RFID rfid(10,5); 

int TarjetaUno[5];

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init(); 
  
  TarjetaUno[0] = 132;
  TarjetaUno[1] = 86;
  TarjetaUno[2] = 118;
  TarjetaUno[3] = 26;
  TarjetaUno[4] = 190;
  
}

void loop()
{ 
 
    if (rfid.isCard()) {
          if (rfid.readCardSerial()) { 
                if (rfid.serNum[0] == TarjetaUno[0] && rfid.serNum[1] == TarjetaUno[1] && rfid.serNum[2] == TarjetaUno[2] && rfid.serNum[3] == TarjetaUno[3] && rfid.serNum[4] == TarjetaUno[4]) 
                {
                    Serial.println("La tarjeta es valida");
                   delay(500);
                }   
                 else
                {
                     Serial.println("La tarjeta no es valida");
                    delay(500);
                 } 
          }
    }  
    rfid.halt();
}*/
