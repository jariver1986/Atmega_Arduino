#include <PZEM004Tv30.h>
#include <Wire.h> 

/* Hardware Serial3 is only available on certain boards.
 * For example the Arduino MEGA 2560
*/

PZEM004Tv30 pzem(&Serial3);

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop() 
{
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();
    Serial.println(String(voltage)+"#"+String(current)+"#"+String(power)+"#"+String(energy)+"#"+String(frequency)+"#"+String(pf));    
    delay(2000);
}
