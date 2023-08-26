#include <Wire.h>
#include <OzOLED.h>
#include <SPI.h>
#include <MFRC522.h>

char texto;
int i=0;
int j=1;
int centinela=0;
const int RST_PIN = 9;            // Pin 9 para el reset del RC522
const int SS_PIN = 10;            // Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crear instancia del MFRC522
 
String printArray(byte *buffer, byte bufferSize) {
  String resultado="";
   for (byte i = 0; i < bufferSize; i++) {
      //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      //Serial.print(buffer[i], HEX);
      //Serial.print(buffer[i], HEX);
      resultado+=String(buffer[i], HEX);
   }
   return resultado;
}


void setup()
{
  Serial.begin(9600);
   SPI.begin();         //Función que inicializa SPI
   mfrc522.PCD_Init();     //Función  que inicializa RFID
  OzOled.init();  //initialze SEEED OLED display
  OzOled.setNormalDisplay();
  OzOled.setHorizontalMode(); 
  OzOled.clearDisplay();
  OzOled.scrollDiagRight();
  delay(1000);
  OzOled.scrollDiagRight();
  delay(1000);
  OzOled.scrollDiagRight();
  delay(1000);
  OzOled.scrollDiagRight();
  delay(1000);
}

void loop()
{

  if (Serial.available()>0)
    {
      OzOled.setPowerOn();
      texto=Serial.read();
      //Serial.print(texto);
      OzOled.printChar(texto,i,1);
      i=i+1;
      if(texto=='@')
      {
        OzOled.setPowerOn();
      }
      if(texto=='#')
      {
        OzOled.setPowerOff();
      }
    }
    else{
      i=0;
      }

       if (mfrc522.PICC_IsNewCardPresent())
   {
      if (mfrc522.PICC_ReadCardSerial())
      {
          //Serial.print(F("ID:"));
         String r=printArray(mfrc522.uid.uidByte, mfrc522.uid.size);
         //Serial.println();
         String enviar=r+"-"+r+"-"+r+"-"+r+"-"+r+"-"+r;
         Serial.println(enviar);
 
         // Finalizar lectura actual
         mfrc522.PICC_HaltA();
      }
   }
    
    
    
}
