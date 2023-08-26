#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
//librerias del DHT 11
int sensor =0;
int sensor2 =1;
int salida=0;
const int buttonPin = 7; 
int buttonState = 0;         
void setup() {
Serial.begin(9600); //Se inicia la comunicación serial 
dht.begin(); //Se inicia el sensor
}

void loop()
{
  ///////////////////////HUMEDAD AMBIENTE////////////////////////////////////
  float h = dht.readHumidity(); //se lee la humedad
  float t= dht.readTemperature(); // se lee la temperatura
  Serial.print("HUMEDAD AMBIENTE: "); 
  Serial.print(h); 
  Serial.print("\n");
  
  //Serial.print("Temperatura: "); 
  //Serial.print(t); 
  //Serial.print("\n");
  ///////////////////////TEMPERATURA////////////////////////////////////
  sensor = analogRead(A0);  
  //salida = map(sensor, 0, 1023, 0, 255);  
  salida = ((sensor * 48875.0)/100000.0); 
  Serial.print("TEMPERATURA: ");
  Serial.print(salida);
  Serial.print("\n");
///////////////////////////////////////////////////////////
///////////////////////HUMEDAD RELATIVA////////////////////////////////////
  sensor2 = analogRead(A1);  
  salida = sensor2;
  Serial.print("HUMEDAD RELATIVA ");
  Serial.print(salida);
  Serial.print("\n");
///////////////////////////////////////////////////////////




  delay(1000); 

}


