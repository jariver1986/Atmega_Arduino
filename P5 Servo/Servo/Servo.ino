#include <Servo.h>

Servo control1;
void setup() 
{
  control1.attach(9);
}

void loop() 
{
    control1.write(0);
    delay(1000);
    control1.write(45);
    delay(1000);
    control1.write(90);
    delay(1000);
    control1.write(45);
    delay(1000);
}
