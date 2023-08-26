// #include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"
#include "DHT.h"

#define D0   16 //GPIO16 - WAKE UP
#define D1   5  //GPIO5
#define D2   4  //GPIO4
#define D3   0  //GPIO0
#define D4   2  //GPIO2 - TXD1

#define D5   14 //GPIO14 - HSCLK
#define D6   12 //GPIO12 - HMISO
#define D7   13 //GPIO13 - HMOSI - RXD2
#define D8   15 //GPIO15 - HCS   - TXD2
#define RX   3  //GPIO3 - RXD0 
#define TX   1  //GPIO1 - TXD0


#define DEVICE  "xxxxx"  // Put here your Ubidots device label
#define VARIABLE  "xxxxx"  // Put here your Ubidots variable label
#define ID_TEMP "xxxxx" 
#define TOKEN  "xxxxx"  // Put here your Ubidots TOKEN

#define WIFISSID "SSID TU ROUTER" // Put here your Wi-Fi SSID
#define PASSWORD "TU CLAVE" // Put here your Wi-Fi password

Ubidots client(TOKEN);
float Valor_Temperatura = 0;

const byte  Pin_led = D8; 
const byte  Obj_DHT22 = D4;   
#define DHTPIN Obj_DHT22     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

DHT Obj_DHT(DHTPIN, DHTTYPE);


void setup() {
    
    Obj_DHT.begin();
    pinMode(Pin_led, OUTPUT);
    digitalWrite(Pin_led, LOW);
    
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
   
    //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() 
{
    float h = Obj_DHT.readHumidity(); //Lee la humedad
    float t = Obj_DHT.readTemperature();//Lee la temperatura en grados centigrados (Valor por defecto)
  
    // verifica si alguna lectura ha fallado
    if (isnan(h) || isnan(t)) {
      Serial.println("Existe un error en la lectura del sensor DHT22!");
      return;
    }

    Serial.println("--------------------------------------------------------");
    Serial.print("Humedad: ");Serial.print(h);Serial.println(" %");
    Serial.print("Temperatura: ");Serial.print(t);Serial.println(" *C");
    Serial.println("--------------------------------------------------------");

    
    float Valor_Led = client.get(DEVICE, VARIABLE);
    
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);
      
      if (Valor_Led==1){digitalWrite(Pin_led, HIGH);}
      else{digitalWrite(Pin_led, LOW);}
      
    }else{
      Serial.println(F("Error getting Valor_Led"));
    }

    Valor_Temperatura = t;
    
    client.add(ID_TEMP, Valor_Temperatura); 
    client.send();
    delay(5000);
}
