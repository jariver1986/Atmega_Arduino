#include "Ubidots.h"
#include<SimpleDHT.h>

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


#define DEVICE  "esp8266_principal"  // Put here your Ubidots device label
#define VARIABLE  "var_led"  // Put here your Ubidots variable label
#define DEVICE2  "luminaria"  // Put here your Ubidots device label
#define VARIABLE2  "luminaria"  // Put here your Ubidots variable label

#define ID_TEMP "Temperatura" 
#define ID_TEMP2 "Humedad" 
#define ID_TEMP3 "MQ135" 
#define TOKEN  "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x"  // Put here your Ubidots TOKEN

#define WIFISSID "Mu" // Put here your Wi-Fi SSID
//#define WIFISSID "NETLIFE-RIVERA_EXT" // Put here your Wi-Fi SSID
#define PASSWORD "0909039109" // Put here your Wi-Fi password

Ubidots client(TOKEN);
float Valor_Temperatura = 0;
float Valor_Humedad = 0;
const byte  Pin_led = D8; 
const byte  Pin_led2 = D7; 
const byte  Pin_led3 = D6; 

int pinDHT11 = 14;
SimpleDHT11 dht11(pinDHT11);
float MQ135=0;
int contador=0;
void setup() 
{
    pinMode(Pin_led, OUTPUT);
    pinMode(Pin_led2, OUTPUT);
    pinMode(Pin_led3, OUTPUT);
    digitalWrite(Pin_led, LOW);    
    digitalWrite(Pin_led2, LOW);    
    digitalWrite(Pin_led3, LOW);    
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
}

void loop() 
{
//++++++++++++++++++++++++++++++++++++++++++++DHT11
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, data)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  float decimal=0.0;
  decimal=(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]);
  float dato= temperature+decimal/10;
  Serial.print("temperatura: ");
  Serial.print(String(dato));
  Serial.print(" C, ");
  Serial.print("Humedad: ");
  Serial.print((int)humidity); 
  Serial.println(" H");

//+++++++++++++++++++++++++++++++++++++++++++++++++MQ135 CALIDAD AIRE
  MQ135=analogRead(A0);
  Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR MQ135: "));
  Serial.println(MQ135);
//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS RX LED
    
    float Valor_Led = client.get(DEVICE, VARIABLE);
    
    if (Valor_Led != ERROR_VALUE)
    {
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);
      
      if (Valor_Led==1)  
      {
        digitalWrite(Pin_led, HIGH);
        client.add(ID_TEMP, Valor_Temperatura); 
        client.send();
        client.add(ID_TEMP2, Valor_Humedad); 
        client.send();
        client.add(ID_TEMP3, MQ135); 
        client.send();
      }
      if (Valor_Led==0)  {digitalWrite(Pin_led, LOW); }  
    }
    else{
      Serial.println(F("Error getting Valor_Led"));
    }

  
//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS RX LUMINARIA
    float lum = client.get(DEVICE2, VARIABLE2);  
    if (lum != ERROR_VALUE)
    {
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL Lum: "));
      Serial.println(lum);
      
      if (lum<50)  {digitalWrite(Pin_led2, LOW);digitalWrite(Pin_led3, LOW);}
      if ((lum>=50)&&(lum<100))   {digitalWrite(Pin_led2, HIGH);digitalWrite(Pin_led3, LOW); }  
      if (lum>=100)   {digitalWrite(Pin_led2, HIGH);digitalWrite(Pin_led3, HIGH); }  
      
    }
    

//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS TX

    Valor_Temperatura = dato;
    Valor_Humedad = humidity;

    
    if ((contador>15)||(contador==0))
    {
    client.add(ID_TEMP, Valor_Temperatura); 
    client.send();
    client.add(ID_TEMP2, Valor_Humedad); 
    client.send();
    client.add(ID_TEMP3, MQ135); 
    client.send();
    contador=0;
    }
    contador++;
    delay(60000);
}
