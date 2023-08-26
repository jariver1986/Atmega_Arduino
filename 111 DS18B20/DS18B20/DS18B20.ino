#include <DS18B20.h>

#define LOW_ALARM 20
#define HIGH_ALARM 25

DS18B20 ds(7);
//DS18B20 ds(8);

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  while (ds.selectNext()) {
    ds.setAlarms(LOW_ALARM, HIGH_ALARM);
  }
}

void loop() {
  ds.doConversion();

  while (ds.selectNextAlarm()) {
    /*Serial.print("Alarm Low: ");
    Serial.print(ds.getAlarmLow());
    Serial.println(" C");
    Serial.print("Alarm High: ");
    Serial.print(ds.getAlarmHigh());
    Serial.println(" C");
    Serial.print("Temperature: ");
    Serial.print(ds.getTempC());
    Serial.println(" C\n");
*/
    //Serial1.print(" ");
    float temp = ds.getTempC();
    //Serial1.print(ds.getTempC());
    Serial.print(temp);
    Serial1.print(temp);
    Serial1.print("@");
  }

  delay(10000);
}
