#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial serialgps(10,11); //RX,TX
int year;
byte month,day,hour,minute,second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
char dato=' ';
int centinela=0;

void setup() 
{
  Serial.begin(115200);
  serialgps.begin(9600);
  
  Serial.println("Senal");  

}


void loop() 
{
      
    while(serialgps.available())
    {
        int c=serialgps.read();
        if(gps.encode(c))
        {
            float latitude, longitude;
            gps.f_get_position(&latitude, &longitude);
            Serial.print("@");
            Serial.print(latitude,5);  
            Serial.print("@=");  
            Serial.print(longitude,5);  
            Serial.println("=");  
            delay(50);
        }
    }
}
