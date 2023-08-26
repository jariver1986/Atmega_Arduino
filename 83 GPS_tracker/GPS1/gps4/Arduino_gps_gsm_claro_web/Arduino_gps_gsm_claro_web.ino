#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
//SoftwareSerial serialgps(1,0);
SoftwareSerial SIM900(7, 8);
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
  Serial.begin(9600);
  //serialgps.begin(9600);
  SIM900.begin(9600);
  //Serial.println("Arduino ok");  
  SIM900.println("AT");
  delay(1000);
  SIM900.println("AT+CMGF=1"); 
  delay(1000);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13, HIGH);                   //Activamos el LED
  digitalWrite(12, HIGH);                   //Activamos el LED
  digitalWrite(11, HIGH);                   //Activamos el LED
  SIM900.println("AT+CNMI=1,2,0,0,0");
  delay(1000);
}

void loop() 
{
      
    while(Serial.available())
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
    }
    conteo=conteo+1;
    delay(10);
    if (SIM900.available())
    {                                //Si hay datos disponibles
      Comando = SIM900.readString();                        //Los almacenamos en la variable Comando
      Serial.println("NUEVO SMS ENTRANTE: " + Comando);      //Los sacamos por comunicacion serie
    } 
    if(Comando.indexOf("#abrir#")>=0)
    {                                            //Si la variable     Comando contiene la palabra ON
      
      digitalWrite(12, LOW);                   //Activamos el LED
      delay(600);
      digitalWrite(12, HIGH);                   //Activamos el LED
      SIM900.println("AT+CMGD=3");
      Comando = "";                              //Vaciamos la variable
    }
    if(Comando.indexOf("#cerrar#")>=0)
    {                                            //Si la variable Comando contiene la palabra ON
      digitalWrite(11, LOW);                   //Activamos el LED
      delay(600);
      digitalWrite(11, HIGH);                   //Activamos el LED
      SIM900.println("AT+CMGD=3");
      Comando = "";                              //Vaciamos la variable
    }
    if(conteo>6000)
    {
              digitalWrite(13, LOW);                   //Activamos el LED
              conteo=0;
              SIM900.println("AT");
              delay(2000);
              SIM900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
              delay(2000);
              SIM900.println("AT+SAPBR=3,1,\"APN\",\"internet.claro.com.ec\"");
              delay(2000);
              SIM900.println("AT+SAPBR =1,1");
              delay(2000);
              SIM900.println("AT+SAPBR=2,1");
              delay(2000);
              SIM900.println("AT+HTTPINIT");
              delay(2000);
              SIM900.println("AT+HTTPPARA=\"CID\",1");
              delay(2000);
              SIM900.println("AT+HTTPPARA=\"URL\",http://www.aplisys.net/pcs/recibe_get2.php?var1="+String(latitude,5)+"&var2="+String(longitude,5));
              delay(2000);
              SIM900.println("AT+HTTPACTION=0");
              delay(2000);
              digitalWrite(13, HIGH);                   //Activamos el LED
              //SIM900.println("AT+HTTPREAD");
              //delay(2000); 
    }
}
