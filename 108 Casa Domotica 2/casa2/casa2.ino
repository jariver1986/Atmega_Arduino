//Acelerometro, campo magnetico, intensidad de luz, reloj, temperatura.
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <SimpleDHT.h>
#include <TimeLib.h>

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;
int gx, gy, gz;
int dato=0;
int pinDHT11 = 3;
SimpleDHT11 dht11(pinDHT11);
int ax_o,ay_o,az_o;
int gx_o,gy_o,gz_o;
void setup() 
{
  Serial.begin(115200);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
  pinMode(2,INPUT);       //Sensor de Campo Magnetico
  setTime(10,51,00,6,9,2021);

  if (sensor.testConnection()){} 
}

void loop() {
  // Hora
      /*Serial.print(day(t));
      Serial.print(+ "/") ;
      Serial.print(month(t));
      Serial.print(+ "/") ;
      Serial.print(year(t)); 
      Serial.print( " ") ;
      */
      Serial.print("Hora ");
      Serial.print(hour());  
      Serial.print(+ ":") ;
      Serial.print(minute());
      Serial.print(":") ;
      Serial.print(second());
      Serial.print("\t");


  
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);

  //Mostrar las lecturas separadas por un [tab]
  //Serial.print("a[x y z] g[x y z]:\t");
  Serial.print("ax=");Serial.print(ax); Serial.print("\t");
  Serial.print("ay=");Serial.print(ay); Serial.print("\t");
  Serial.print("az=");Serial.print(az); Serial.print("\t");
  //Serial.print(gx); Serial.print("\t");
  //Serial.print(gy); Serial.print("\t");
  //Serial.println(gz);

  

 //Sensor campo magnetico
  int estado=digitalRead(2);
  Serial.print("Campo Magnetico =");
  if(estado==HIGH)
  {
    Serial.print("High");
  }
  else {Serial.print("Low");}
  Serial.print("\t");

  //Sensor Luz
  dato=analogRead(A0);
  //Serial.println(dato);
  Serial.print("Iluminacion: " + String(((500-dato)*100)/500)+"%");
  Serial.print("\t");
  

  //Sensor de temperatura
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  //Serial.print("Sample OK: ");
  //Serial.print("\t");
  Serial.print("Temperatura: "+String(temperature)); Serial.println("C"); 
  //Serial.print((int)humidity); Serial.println(" H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
  
  //delay(100);
}
