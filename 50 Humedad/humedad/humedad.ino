#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
//librerias del DHT 11
void setup() {
Serial.begin(9600); //Se inicia la comunicación serial 
dht.begin(); //Se inicia el sensor
Serial.println("CLEARDATA");
Serial.println("LABEL,Date,Time,Humedad");  
}
void loop()
{
  float h = dht.readHumidity(); //se lee la humedad
  float t= dht.readTemperature(); // se lee la temperatura
  Serial.print( (String) "DATA,DATE,TIME,");
  //Serial.print(t);
  //Serial.print(" / ");
  Serial.println(h);
  delay(1000); 
}


