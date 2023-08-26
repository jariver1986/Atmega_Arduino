#include <Servo.h>
 
int const leftSensorPin = A0;
int const rightSensorPin = A1;
 
Servo myServo;
 
int angle = 90;
int leftSensorValue = 0;
int rightSensorValue = 0;
// Es casi imposible que left y right sean exactamente iguales por lo que el motor
// no se detendra, le voy a poner un colchon en el que considere left = right para
// que se detenga cuando esté en ese rango. Este valor se puede ir ajustando para lograr
// la precisión deseada sin que perjudique el funcionamiento del sistema
int colchon = 50;
 
void setup(){
  myServo.attach(11);
  Serial.begin(9600);
  // Ponemos inicialmente el motor en 2º, no usar 0, puede dar vibraciones en el motor
  // si este no consigue alcanzar los 0º
  myServo.write(angle);
}


 
void loop(){
  
 
  leftSensorValue = analogRead(leftSensorPin);
  delay(10);
  rightSensorValue = analogRead(rightSensorPin);
  delay(10);
  Serial.print("Left Sensor Value: ");
  Serial.print(leftSensorValue);
  Serial.print(" - Right Sensor Value: ");
  Serial.print(rightSensorValue);
  Serial.print(" - Angle: ");
  Serial.println(angle);
 
  if (rightSensorValue > leftSensorValue && angle > 5 && rightSensorValue-leftSensorValue > colchon){
    angle = angle - 5;
    myServo.write(angle);
  }
  if (rightSensorValue < leftSensorValue && angle < 175 && leftSensorValue-rightSensorValue > colchon){
    angle = angle + 5;
    myServo.write(angle);
  }
  else
    //Este equilibrado, no mover
  delay(15); // Ponemos un delay para que la placa pueda procesar los valores
}
