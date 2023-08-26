#include "UbidotsESPMQTT.h"
#include <Wire.h>
#include <MPU6050.h>


             //
#define TOKEN "BBFF-C3l6cH330EXZ0gUkqZc0o0eAB6Ilkp" // Your Ubidots TOKEN
#define WIFINAME "Arduino" //Your SSID
#define WIFIPASS "12345678" // Your Wifi Pass
Ubidots client(TOKEN);

//const int alarma = 2;
MPU6050 mpu;
int anterior=0;
int actual=0;
int prom=0;
int alarma=0;


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup() 
{
  
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);

  Serial.begin(115200);
  Wire.begin();
  //pinMode(alarma, OUTPUT);
  //digitalWrite(alarma, LOW);
  mpu.initialize();
  mpu.setDLPFMode(0);  // Desactivar el filtro de paso bajo
  mpu.setFullScaleAccelRange(2); // Rango de aceleración +/- 2g
  mpu.setFullScaleGyroRange(250); // Rango de velocidad angular +/- 250 grados/segundo
}

void loop() 
{
  int16_t ax, ay, az, gx, gy, gz;

  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  anterior=actual;
  actual=ax;
  int estabilidad = abs(abs(actual)-abs(anterior));
  Serial.println("Estabilidad: "+String(estabilidad));
  Serial.println("Valor X= " + String(ax));
  Serial.println("Valor Y= " + String(ay));
  Serial.println("Valor Z= " + String(ax));
  if(estabilidad>500)
  {
    Serial.print("Alerta ");
    alarma=1;
  }
  else
  {
    alarma=0;
  }
    
  
   
  //Serial.println(ay);
  //Serial.println(az);
  
  if(!client.connected())
  {
      client.reconnect();
  }   
  client.add("x", ax); 
  client.add("y", ay); 
  client.add("z", az);
  client.add("W", alarma);  
  client.ubidotsPublish("Datos1");
  client.loop();

  /*Serial.print("Giro: ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.println(gz);
  */
  delay(1000); // Pausa para evitar lecturas demasiado rápidas
}
