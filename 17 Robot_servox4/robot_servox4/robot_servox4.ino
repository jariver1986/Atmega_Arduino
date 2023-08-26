#include <Ultrasonic.h>
#include <Servo.h>

Ultrasonic ultrasonic(10,11,3000); // (Trig PIN,Echo PIN, TIMEOUT)

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
  Serial.print(ultrasonic.Ranging(CM)); // CM or INC
  Serial.println(" cm" );
  delay(100);
  if ((ultrasonic.Ranging(CM)) < 50)
  {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
  }
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    ///////////////////////////SUPERIOR IZQUIERDA
  //}
    if(option=='q') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO SUPERIOR IZQUIERDA ADELANTE ");
      miServo1.write(0);
    }
    if(option=='w') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO SUPERIOR IZQUIERDA ATRAS ");
      miServo1.write(90);
    }

    //////////////////////////////SUPERIOR DERECHA
    if(option=='p') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO SUPERIOR DERECHA ADELANTE ");
      miServo2.write(0);//180
    }
    if(option=='o') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO SUPERIOR DERECHA ATRAS ");
      miServo2.write(90);//90
    }
   
    ///////////////////////////INFERIOR IZQUIERDA
    if(option=='a') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO INFERIOR IZQUIERDA ADELANTE ");
      miServo3.write(0);
    }
    if(option=='s') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO INFERIOR IZQUIERDA ATRAS ");
      miServo3.write(90);
    }

    //////////////////////////////INFERIOR DERECHA
    if(option=='l') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO INFERIOR DERECHA ADELANTE ");
      miServo4.write(0);
    }
    if(option=='k') 
    {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      Serial.println("SERVO INFERIOR DERECHA ATRAS ");
      miServo4.write(90);
    }
  }   
  
}
