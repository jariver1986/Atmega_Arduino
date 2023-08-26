#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial serialgps(4,3); //RX,TX
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
            Serial.println(String(latitude,5)+String(longitude,5)+"@");
            /*Serial.print(latitude,5);  
            Serial.print("@=");  
            Serial.print(longitude,5);  
            Serial.println("=");  */
            delay(5000);
        }
    }
}
