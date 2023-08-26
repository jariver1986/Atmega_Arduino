#include <Servo.h>
long distancia;
long tiempo;

int option=0;
int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 11;      // connect Red LED to pin 11 (PWM pin)
int BANDA = 12;      // connect Red LED to pin 11 (PWM pin)

int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;
Servo miServo1;
Servo miServo2;
int contador=0;
int tacho=0;
int centinela=2;
 
void setup(void) 
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(LEDpin, OUTPUT);
  pinMode(BANDA, OUTPUT);
  digitalWrite(BANDA, HIGH);
  miServo1.attach(3);
  miServo2.attach(6);
  miServo1.write(0);
  miServo2.write(50);
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
}
 
void loop(void) 
{

  if (Serial.available()>0)
    {
      //leemos la opcion enviada
      option=Serial.read();
      if(option=='1') 
      {
        centinela=1;
        option=0;
        
      }
      if(option=='2') 
      {
        centinela=2;
        option=0;
        
      }
      if(option=='3') 
      {
        miServo2.write(50);
        delay(500);
        option=0;
        
      }if(option=='4') 
      {
        miServo2.write(0);
        delay(500);
        option=0;
        
      }
      if(option=='5') 
      {
        miServo2.write(50);
        delay(1000);
        miServo2.write(0);
        delay(1000);
        miServo2.write(50);
        option=0;
        
      }
      
    }

if(centinela==1)
{  
  fsrReading = analogRead(fsrAnalogPin);
  digitalWrite(BANDA, LOW);
  if(fsrReading<100)
  {
     
  }
  else
  {
    tacho = tacho +1;
    digitalWrite(BANDA, HIGH);
    Serial.print(fsrReading);
    Serial.print("@");  
    Serial.print(tacho);
    Serial.println(";P");  
    delay(1000);

    for(int i=50;i>0;i--)
    {
      miServo2.write(i);
      delay(40);
    }
    delay(500);
    miServo2.write(50);
    delay(3000);
  }
  
}
  if (centinela==2)
  {
    digitalWrite(BANDA, HIGH);
  }
}


