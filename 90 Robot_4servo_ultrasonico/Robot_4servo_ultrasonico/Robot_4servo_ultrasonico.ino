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

  miServo1.write(0);
  miServo2.write(90);
  miServo3.write(90);
  miServo4.write(0);
  
  digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
}
 
void loop()
{
  //Serial.print(ultrasonic.Ranging(CM)); // CM or INC
  //Serial.println(" cm" );
  delay(100);
  if ((ultrasonic.Ranging(CM)) < 50)
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
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    ///////////////////////////SUPERIOR IZQUIERDA
  //}
    if(option=='1') 
    {
      
      miServo1.write(90);
      
    }
    if(option=='2') 
    {
      
      miServo1.write(0);
      
    }
    if(option=='A') 
    {
      
      miServo1.write(90);
      delay(1000);
      miServo1.write(0);
      delay(500);
    }

    //////////////////////////////SUPERIOR DERECHA
    if(option=='3') 
    {
      
      miServo2.write(0);//180
    }
    if(option=='4') 
    {
      
      miServo2.write(90);//90
    }
    if(option=='B') 
    {
      
      miServo2.write(0);
      delay(1000);
      miServo2.write(90);
      delay(500);
    }
   
    ///////////////////////////INFERIOR IZQUIERDA
    if(option=='5') 
    {
      
      miServo3.write(0);
    }
    if(option=='6') 
    {
      
      miServo3.write(90);
    }
    if(option=='C') 
    {
      
      miServo3.write(0);
      delay(1000);
      miServo3.write(90);
      delay(500);
    }
    //////////////////////////////INFERIOR DERECHA
    if(option=='7') 
    {
      
      miServo4.write(90);
    }
    if(option=='8') 
    {
      
      miServo4.write(0);
    }
    if(option=='D') 
    {
      
      miServo4.write(90);
      delay(1000);
      miServo4.write(0);
      delay(500);
    }
  }   
  
}
