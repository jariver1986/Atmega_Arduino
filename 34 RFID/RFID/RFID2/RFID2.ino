#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN); 
// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;
    float cont;
    float cont2;
void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  cont=0;
  cont2=0;
}
void loop()
{
    if (rfid.isCard()) 
    {
      if (rfid.readCardSerial()) 
          {
              serNum0 = rfid.serNum[0];
              serNum1 = rfid.serNum[1];
              serNum2 = rfid.serNum[2];
              serNum3 = rfid.serNum[3];
              serNum4 = rfid.serNum[4];
              if (serNum0==228)
              {
                  cont= cont + 0.30;
              }
              if (serNum0==96)
              {
                  cont2= cont2 + 0.30;
              }
           }       
    }
    Serial.println("CARD1:"+ String(cont));
    Serial.println("CARD2:"+ String(cont2));  
    Serial.println(); 
    delay(1000);
    rfid.halt();
}

