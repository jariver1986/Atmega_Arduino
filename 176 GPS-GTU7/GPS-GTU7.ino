#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial serialgps(10,11); //RX,TX ARDUINO MEGA, NO TODOS LOS PINES MANEJAM INTERRUPCION
int year;
byte month,day,hour,minute,second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
char dato=' ';
int centinela=0;
float latitude, longitude;
void setup() 
{
  Serial.begin(115200);
  serialgps.begin(9600);
  
  Serial.println("Senal");  

}


void loop() 
{
  if(Serial.available()>0)
  {
    int dato=Serial.read();
    if (dato=='1')
    {
      Serial.print("Lat:");
      Serial.println(latitude,5);  
      Serial.print("Lon:");  
      Serial.println(longitude,5);  
      dato=0;      
    }
  }
  while(serialgps.available())
  {
    int c=serialgps.read();
    if(gps.encode(c))
    {
      gps.f_get_position(&latitude, &longitude);
      
    }
  }   
    
}
