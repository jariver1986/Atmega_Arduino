#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // Configura el puerto serial para el SIM900
int option=0;
void setup()
{
  //SIM900.begin(19200); //Configura velocidad del puerto serie para el SIM900
  SIM900.begin(9600); //Configura velocidad del puerto serie para el SIM900
  //Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  Serial.begin(9600); //Configura velocidad del puerto serie del Arduino
  Serial.println("OK");
  delay (1000);
  SIM900.println("AT"); //Comando AT para introducir el PIN de la tarjeta
  delay(1000); //Tiempo para que encuentre una RED
}

void loop() 
{
    if (Serial.available()>0)
    {
        option=Serial.read();
        if(option=='1') 
        {
        SIM900.println("AT");
        Serial.println("OK");
        
        }
        if(option=='2') 
        {
          SIM900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
          delay(1000);
          SIM900.println("AT+SAPBR=3,1,\"APN\",\"internet.claro.com.ec\"");
          delay(1000);
          SIM900.println("AT+SAPBR =1,1");
          delay(1000);
          SIM900.println("AT+SAPBR=2,1");
          delay(1000);
          SIM900.println("AT+HTTPINIT");
          delay(1000);
          SIM900.println("AT+HTTPPARA=\"CID\",1");
          delay(1000);
          SIM900.println("AT+HTTPPARA=\"URL\",http://www.aplisys.net/pcs/recibe_get2.php?var1=7777777.00&var2=8888888.00");
          delay(1000);
          SIM900.println("AT+HTTPACTION=0");
          delay(1000);
          SIM900.println("AT+HTTPREAD");
          delay(1000); 
          Serial.println("OK GSM");   
        }
    }
    
}
