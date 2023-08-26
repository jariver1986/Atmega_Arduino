/*
 Lectura de datos de temperatura y humedad con sensor DHT22 y placa 
 NodeMCU y monitorización en la plataforma www.thinger.io

 Este código de ejemplo es de público dominio.
 Dani No www.esploradores.com
 */

#include <ESP8266WiFi.h>       //Librería de conexión WiFi del módulo ESP8266
#include <ThingerESP8266.h>    //Librería de la plataforma thinger.io

// Parámetros del conexión con thinger.io
#define usuario "proyectoiot" //titulo de usuario thnder
#define device_Id "sensores"//device ID
//#define device_credentials "1234567"
#define device_credentials "7654321"

ThingerESP8266 thing(usuario, device_Id, device_credentials);

// Parámetros de conexión WiFi
//const char WiFi_ssid[]="INNACENSA";            //Nombre de red
//const char WiFi_password[]="innacensa.";  //Clave de red

const char WiFi_ssid[]="INTERNET CNT";            //Nombre de red
const char WiFi_password[]="cualeslaclave";  //Clave de red

//const char WiFi_ssid[]="Mu";            //Nombre de red
//const char WiFi_password[]="john2017";  //Clave de red

String dato;
String dato2;
void setup() 
{
Serial.begin(115200);
  
   if (Serial.available()>0)
  {
    dato=Serial.readStringUntil('T');
    Serial.println(dato);
    dato2=Serial.readStringUntil('P');
    Serial.println(dato2);
  } //(temperatura)+T+(ph)+P
   



  
  // Inicialización de la WiFi para comunicarse con la API
  thing.add_wifi(WiFi_ssid, WiFi_password);
  // Inicialización de la lectura de datos desde la API
  thing["dht22"] >> [](pson& out){
    out["Temperatura"] = dato;//dht.readTemperature();
    out["PH"] = dato2;//dht.readHumidity();
    };
  }

void loop() 
{
  thing.handle();
  if (Serial.available()>0)
  {
    dato=Serial.readStringUntil('T');
    Serial.println(dato);
    dato2=Serial.readStringUntil('P');
    Serial.println(dato2);
  }
  }
