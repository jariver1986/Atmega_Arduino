#include <DS18B20.h>
DS18B20 ds(D1);

#define LOW_ALARM 20
#define HIGH_ALARM 25


void setup() 
{
  Serial.begin(115200);
  while (ds.selectNext()) 
  {
    ds.setAlarms(LOW_ALARM, HIGH_ALARM);
  }
}

void loop() 
{ 
  ds.doConversion();
  while (ds.selectNextAlarm()) 
  {
    float temp = ds.getTempC();
    Serial.println("T: "+ String(temp));
  }
  delay(10000);
}
