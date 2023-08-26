#include <Servo.h>

int option;
int led = 13;
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
  miServo3.attach(2);
  miServo4.attach(9);

  miServo1.write(90);
  miServo2.write(90);
  miServo3.write(90);
  miServo4.write(90);
}
 
void loop()
{
  delay(100);
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("Cerrado");
      miServo1.write(0);
    }
    if(option=='2') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("Abierto");
      miServo1.write(90);
    }

    //////////////////////////////SUPERIOR DERECHA
    if(option=='3') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("Abierto");
      miServo1.write(0);//180
    }
    if(option=='4') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("Cerrado");
      miServo1.write(180);//90
    }
   
  }   
  
}
