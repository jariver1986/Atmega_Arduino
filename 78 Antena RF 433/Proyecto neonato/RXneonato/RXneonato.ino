#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
//#include <SoftwareSerial.h>

RH_ASK driver;
int alerta=0;
int contador=0;
int dato=0;
//SoftwareSerial SIM900(8, 9);

void setup()
{
    Serial.begin(9600); // Debugging only
    Serial1.begin(9600); // Debugging only
    pinMode(13,OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(13, LOW); 
    digitalWrite(7,LOW);
    if (!driver.init())
         Serial.println("init failed");

    

}
void llamar()
   {
      Serial.println("AT");  //Comando AT para realizar una llamada
      //SIM900.println("AT");
      delay(3000);
      Serial.println("ATD0987213468;");  //Comando AT para realizar una llamada
      //SIM900.println("ATD043092223;");  //Comando AT para realizar una llamada
      //delay(10000);  // Espera 30 segundos mientras realiza la llamada
      //Serial.println("ATH");  // Cuelga la llamada
      //delay(3000);
      
   }

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      //Serial.print("Message: ");
      //Serial.println((char*)buf);
      //delay(100);
      Serial1.println((char*)buf);
      delay(100);    
      
    }  
    if (Serial1.available()>0)
    {
      dato=Serial1.read();
      if(dato=='1')
      {
        alerta=1;
      }
      dato=0;
    } 
    
    if(alerta==1)
    {
      while(contador<3)
      {
        
      digitalWrite(7,HIGH);
      digitalWrite(13,HIGH);
      delay(200); 
      digitalWrite(7,LOW); 
      digitalWrite(13,LOW);
      delay(200);
      digitalWrite(7,HIGH);
      digitalWrite(13,HIGH);
      delay(200); 
      digitalWrite(7,LOW);
      digitalWrite(13,LOW); 
      delay(200); 
      contador=contador+1;
      }
      llamar();
      contador=0;
      alerta=0;
    }
  
}
