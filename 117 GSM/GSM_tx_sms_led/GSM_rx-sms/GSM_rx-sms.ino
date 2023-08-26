#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
//SoftwareSerial serialgps(1,0);
SoftwareSerial SIM900(2,3); //RX, TX Serial
int year;
byte month,day,hour,minute,second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
char dato=' ';
int centinela=0;
int option=0;
float latitude, longitude;
int conteo=0;
String Comando;


void setup() 
{
  Serial.begin(115200);
  //serialgps.begin(9600);
  SIM900.begin(9600);
  //Serial.println("Arduino ok");  
  SIM900.println("AT");
  delay(1000);
  SIM900.println("AT+CMGF=1"); 
  delay(1000);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);                   //Activamos el LED
  SIM900.println("AT+CNMI=1,2,0,0,0");
  delay(1000);
}

void loop() 
{
   /* while(Serial.available())
    {
        int c=Serial.read();
        if(gps.encode(c))
        {
            gps.f_get_position(&latitude, &longitude); 
            
            Serial.print("@");
            Serial.print(latitude,5);  
            Serial.print("@=");  
            Serial.print(longitude,5);  
            Serial.println("=");
            delay(2000);            
        }              
    }*/
   if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='a') {
      digitalWrite(12, LOW);
      Serial.println("ON");
    }
    if(option=='b') {
      digitalWrite(12, HIGH);
      Serial.println("OFF");
    }
    if(option=='c') {
      
      Serial.println("encerado");
      Comando = "";
    }
    option=0;
  }
    
    
    delay(10);
    if (SIM900.available())
    {                                //Si hay datos disponibles
      Comando = SIM900.readString();                        //Los almacenamos en la variable Comando
      Serial.println("NUEVO SMS ENTRANTE: " + Comando);      //Los sacamos por comunicacion serie
    } 
    if(Comando.indexOf("#ON#")>=0)
    {                                            //Si la variable     Comando contiene la palabra ON
      digitalWrite(12, LOW);                   //Activamos el LED
      SIM900.println("AT+CMGD=3");
      Comando = "";                              //Vaciamos la variable
      Serial.println("Mensaje #ON# recibido");
    }
    if(Comando.indexOf("#OFF#")>=0)
    {                                            //Si la variable Comando contiene la palabra ON
      digitalWrite(12, HIGH);                   //Activamos el LED
      SIM900.println("AT+CMGD=3");
      Comando = "";                              //Vaciamos la variable
      Serial.println("Mensaje #OFF# recibido");
    }
}
