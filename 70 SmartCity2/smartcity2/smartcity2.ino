#include <Servo.h>

int option;
int option2;
int sensor=0;
int sensor2=0;
int out2 = 13;
int led = 11;
Servo miServo1;
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
 
  pinMode(out2, OUTPUT); 
  pinMode(led, OUTPUT); 
  miServo1.attach(2);
  miServo1.write(0);
  
}
void loop()
{
  
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(out2, LOW);
      delay(3000);
      digitalWrite(out2, HIGH);
      delay(3000);
      option=0;
      Serial.println("Luces encendidas");
    }
   
  }

if (Serial1.available()>0)
  {
    //leemos la opcion enviada
    option2=Serial1.read();
     if(option2=='A') 
    {
      Serial.println("Garita Abierta");
      miServo1.write(90);
    }
    if(option2=='C') 
    {
      Serial.println("Garita Cerrada");
      miServo1.write(0);
    }
  }






  
  sensor= (analogRead(0)*100)/1000;
  if(sensor>65) 
  {
   digitalWrite(out2, HIGH);
  }
  else
  {
    digitalWrite(out2, LOW);
    }
    Serial.print("Luz: ");
   Serial.println(sensor);
  
   sensor2= (analogRead(1)*100)/1000;
  if(sensor2<65) 
  {
    Serial.print("Sin basura: ");
   digitalWrite(led, LOW);
   Serial.println(sensor2);
   
  }
  else
  {
    digitalWrite(led, HIGH);
     Serial.print("Basura LLena: ");
   Serial.println(sensor2);
   Serial1.print("1");
    }
   
  delay(2000);
}
