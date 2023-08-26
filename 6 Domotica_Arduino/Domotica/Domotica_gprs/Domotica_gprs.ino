#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(7, 8);
/////////////////////
int option='a';
int led = 13;
int centinela;
int sensor = 0;
int salida = 0;
/////////////////////
void setup()
{
  ///////////////////////
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
  ///////////////////////
  gprsSerial.begin(19200);
  Serial.begin(19200);

  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");
  delay(100);
  toSerial();


  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"internet.claro.com.ec\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
}


void loop()
{
   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   // set http param value
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://YOUR.DOMAIN.COM/rest/receiveSensorData?sensorval1=blah&sensorval2=blah\"");
   delay(2000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(6000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   delay(10000);
}

void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.write("x"));
        if (Serial.available()>0)
        {
          //leemos la opcion enviada
          option=Serial.read();
          
          if(option=='a') 
          {
            digitalWrite(led, HIGH);              // ACTIVA RELAY DE LA PUERTA
            delay(1000);
            digitalWrite(led, LOW);               // DESACTIVA RELAY DE LA PUERTA Y PROTEGE SELENOIDE
            delay(100);
            centinela = 0;                        // DESSACTIVA ALARMA
          }
          if(option=='c') 
          {
            digitalWrite(led, HIGH);              // ACTIVA RELAY DE LA PUERTA
            delay(1000);
            digitalWrite(led, LOW);               // DESACTIVA RELAY DE LA PUERTA Y PROTEGE SELENOIDE
            delay(100);
            centinela = 0;                        // DESSACTIVA ALARMA
          }
          if(option=='b') 
          {
            centinela = 1;
            Serial.println(" SISTEMA EN ALERTA "); // ENVIA MENSAJE A TELEFONO
          }
        }
        sensor = analogRead(A0);
        salida = map(sensor, 0, 1023, 0, 255); 
        //Serial.println(sensor);
        if (option=='b')
        {
          if(salida>100)
          {
            Serial.println("int");
          }
        }
    
  }
}
