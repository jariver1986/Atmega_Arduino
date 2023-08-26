#include "Ubidots.h"

#define DEVICE  "esp8266_principal"  // Para kectura desde Ubidots
#define VARIABLE  "var_led"  // Para kectura desde Ubidots

#define DEVICE4  "humedad_tierra"  // Para lectura desde Ubidots
#define VARIABLE4  "var_humedad_tierra"  // Para kectura desde Ubidots

#define ID_TEMP4 "MH"      //Datos a enviar a ubidots
#define TOKEN  "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x"  // Put here your Ubidots TOKEN

#define WIFISSID "Mu2" // Put here your Wi-Fi SSID
//#define WIFISSID "NETLIFE-RIVERA_EXT" // Put here your Wi-Fi SSID
#define PASSWORD "0909039109" // Put here your Wi-Fi password

Ubidots client(TOKEN);
int contador=0;
void setup() 
{
    pinMode(2,INPUT);
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
}

void loop() 
{
//++++++++++++++++++++++++++++++++++++++++++++SENSOR HUMEDAD TIERRA
  int estado=digitalRead(2);
  if(estado==HIGH)
  {
    Serial.println("Humedo ");
  }
  else {Serial.println("Seco ");}
       
//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS TX

    float Valor_Humedad_tierra = estado;
    client.add(ID_TEMP4, Valor_Humedad_tierra); 
    client.send();
    delay(10000);
}
