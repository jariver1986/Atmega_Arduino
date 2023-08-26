#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Ultrasonic.h>
Ultrasonic sensor(6,7,23200);
int dato=0;
int contador=0;

RH_ASK driver;

void setup()
{
    Serial.begin(9600);   // Debugging only
    pinMode(13,OUTPUT);
    digitalWrite(13, LOW); 
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    dato=sensor.Ranging(CM);
    Serial.print("Distancia= ");
    Serial.println(dato);
    delay(1000);
    if(dato<15)
    {
      contador=contador+1;
    }

    if (contador>3)
    {
    const char *msg = "AA@B;_";
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      Serial.println("Alerta");
      digitalWrite(13,HIGH);
      delay(200); 
      digitalWrite(13,LOW); 
      delay(200); 
      digitalWrite(13,HIGH);
      delay(200); 
      digitalWrite(13,LOW); 
      delay(7000);  
      contador=0;
    }
    
    /*else
    {
      const char *msg = "B";
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      Serial.println("No Alerta");
      delay(1000);
    }
    */
}
