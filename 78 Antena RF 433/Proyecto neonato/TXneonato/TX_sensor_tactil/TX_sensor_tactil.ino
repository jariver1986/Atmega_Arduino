#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Ultrasonic.h>
int dato=0;
int contador=0;

RH_ASK driver;

void setup()
{
    Serial.begin(9600);   // Debugging only
    pinMode(13,OUTPUT);
    pinMode(2,INPUT);
    digitalWrite(13, LOW); 
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    
    if(digitalRead(2)==HIGH)
    {
      const char *msg = "AA@B;_";
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      //Serial.println("Alerta");
      digitalWrite(13,HIGH);
      delay(200); 
      digitalWrite(13,LOW); 
      delay(200); 
      digitalWrite(13,HIGH);
      delay(200); 
      digitalWrite(13,LOW); 
    }
    else
    {
      //Serial.println("No Alerta");
    }
    delay(1000);
    
}
