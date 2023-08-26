#include <Ultrasonic.h>
#include <Servo.h>

Ultrasonic ultrasonic(6,7,23200); 

int option;
int led = 2;
Servo miServo1;
Servo miServo2;
Servo miServo3;
Servo miServo4;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
  miServo1.attach(3);
  miServo2.attach(5);
  miServo3.attach(10);
  miServo4.attach(9);

  miServo1.write(90);
  delay(2000);
  miServo2.write(90);
  delay(1000);
  
  
}
 
void loop()
{
  //Serial.print(ultrasonic.Ranging(CM)); // CM or INC
  //Serial.println(" cm" );
  delay(100);
  if ((ultrasonic.Ranging(CM)) < 10)
  {
      
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
  }
  if (((ultrasonic.Ranging(CM)) > 10)&&((ultrasonic.Ranging(CM)) < 20))
  {
      
      miServo1.write(90);
      delay(700);
      miServo2.write(0);
      delay(700);
  }
  if (((ultrasonic.Ranging(CM)) > 20)&&((ultrasonic.Ranging(CM)) < 30))
  {
      
      miServo1.write(0);
      delay(700);
      miServo2.write(90);
      delay(5700);
  }
  Serial.println(ultrasonic.Ranging(CM));
  delay(50);
      
      
   
  
}
