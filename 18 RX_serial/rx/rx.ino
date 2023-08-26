#include <LiquidCrystal.h>
int incomingByte = 0;   // for incoming serial data
String chaine = "";
void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
 
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    char fromSerial = incomingByte;
    if (fromSerial != 4) 
    {
      chaine = chaine + fromSerial;
    }  

    
    if (chaine=="1200")
    {
        Serial.print("ok");
        
    }
    else
    {
      String chaine = "";
      fromSerial=0;
    }

  }
}


