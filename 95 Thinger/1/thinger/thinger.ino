/*
 Lectura de datos de temperatura y humedad con sensor DHT22 y placa 
 NodeMCU y monitorización en la plataforma www.thinger.io

 Este código de ejemplo es de público dominio.
 Dani No www.esploradores.com
 */

#include <ESP8266WiFi.h>       //Librería de conexión WiFi del módulo ESP8266
#include <ThingerESP8266.h>    //Librería de la plataforma thinger.io
#include "DHT.h"               //Librería de los sensores DHT11, DHT22, etc. 

// Parámetros del conexión con thinger.io
#define usuario "ESPloradores"
#define device_Id "DHT22"
#define device_credentials "B7#UXE#t8#7f"

ThingerESP8266 thing(usuario, device_Id, device_credentials);

// Parámetros de conexión WiFi
const char WiFi_ssid[]="JAZZTEL";            //Nombre de red
const char WiFi_password[]="sDFbsREs4yeqq";  //Clave de red

// Parámetros del DHT 
#define DHTPIN D4       //Pin de conexión - GPIO02
#define DHTTYPE DHT22   //Modelo

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  // Inicialización del DHT22  
  dht.begin();

  // Inicialización de la WiFi para comunicarse con la API
  thing.add_wifi(WiFi_ssid, WiFi_password);

  // Inicialización de la lectura de datos desde la API
  thing["dht22"] >> [](pson& out){
    out["Temperatura"] = dht.readTemperature();
    out["Humedad"] = dht.readHumidity();
    };
  }

void loop() {
  thing.handle();
  }
