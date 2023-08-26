#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
//librerias del DHT 11
int sensor =0;
int salida=0;
const int buttonPin = 7; 
int buttonState = 0;         
void setup() {
Serial.begin(9600); //Se inicia la comunicación serial 
dht.begin(); //Se inicia el sensor
}

void loop()
{
  float h = dht.readHumidity(); //se lee la humedad
  float t= dht.readTemperature(); // se lee la temperatura
  Serial.print("Humedad: "); 
  Serial.print(h); 
  Serial.print("\n");
  Serial.print("Temperatura: "); 
  Serial.print(t); 
  Serial.print("\n");
///////////////////////////////////////////////////////////
  sensor = analogRead(A0);
  //salida = map(sensor, 0, 1023, 0, 255);  
  salida = 100.0 -(( sensor * 100.0)/1024.0); 
  Serial.print("Intensidad Luz: ");
  
  Serial.print(salida);
  Serial.print("\n");
///////////////////////////////////////////////////////////
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) 
  {
    
    Serial.print("Con lluvia"); 
    Serial.print("\n");
  } 
  else 
  {

    Serial.print("Sin lluvia"); 
    Serial.print("\n");
  }




  delay(1000); 

}


