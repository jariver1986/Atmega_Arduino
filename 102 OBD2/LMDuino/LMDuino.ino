#include <SoftwareSerial.h>
#include "ELMduino.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


SoftwareSerial mySerial(10,11); // RX, TX
LiquidCrystal_I2C lcd(0x27,20,4);
#define ELM_PORT mySerial


ELM327 myELM327;


uint32_t rpm = 0;


void setup()
{
#if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif

  Serial.begin(115200);
  ELM_PORT.begin(38400);
  Serial1.begin(9600);

  Serial.println("Attempting to connect to ELM327...");

  if (!myELM327.begin(ELM_PORT))
  {
    Serial.println("Couldn't connect to OBD scanner");
    while (1);
  }
  Serial.println("Connected to ELM327");
  
  lcd.init();
  lcd.backlight();
  //Display Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("OBD2");
  lcd.setCursor(0, 1);
  lcd.print("Welcome");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  
  
}


void loop()
{
  float tempRPM = myELM327.rpm();
  if (myELM327.status == ELM_SUCCESS)
  {
    lcd.clear();
    rpm = (uint32_t)tempRPM;
    Serial.print("RPM: "); Serial.println(rpm);
    lcd.setCursor(10, 1); lcd.print(rpm);
    Serial.println("__@"+String(rpm)+";_");
  }
  else
    printError();
}


void printError()
{
  Serial.print("Received: ");
  for (byte i = 0; i < myELM327.recBytes; i++)
    Serial.write(myELM327.payload[i]);
  Serial.println();
  
  if (myELM327.status == ELM_SUCCESS)
    Serial.println(F("\tELM_SUCCESS"));
  else if (myELM327.status == ELM_NO_RESPONSE)
    Serial.println(F("\tERROR: ELM_NO_RESPONSE"));
  else if (myELM327.status == ELM_BUFFER_OVERFLOW)
    Serial.println(F("\tERROR: ELM_BUFFER_OVERFLOW"));
  else if (myELM327.status == ELM_UNABLE_TO_CONNECT)
    Serial.println(F("\tERROR: ELM_UNABLE_TO_CONNECT"));
  else if (myELM327.status == ELM_NO_DATA)
    Serial.println(F("\tERROR: ELM_NO_DATA"));
  else if (myELM327.status == ELM_STOPPED)
    Serial.println(F("\tERROR: ELM_STOPPED"));
  else if (myELM327.status == ELM_TIMEOUT)
    Serial.println(F("\tERROR: ELM_TIMEOUT"));
  else if (myELM327.status == ELM_TIMEOUT)
    Serial.println(F("\tERROR: ELM_GENERAL_ERROR"));

  delay(100);
}
