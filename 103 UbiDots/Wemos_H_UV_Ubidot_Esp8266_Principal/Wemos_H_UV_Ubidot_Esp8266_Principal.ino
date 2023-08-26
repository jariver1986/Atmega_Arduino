/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

//BOTON
//#define DEVICE  "esp8266_principal"  // Put here your Ubidots device label 
//BOTON
//#define VARIABLE  "led_wemos"  // Put here your Ubidots variable label 


/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Mu"; // Put here your Wi-Fi SSID
//const char* WIFI_SSID = "Mu2"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "0909039109"; // Put here your Wi-Fi password

//descomentar
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

//BOTON
//Ubidots client(UBIDOTS_TOKEN);  

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() 
{
  //Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  pinMode(5,INPUT); //PIN D1
  pinMode(16, OUTPUT); //PIN D4 LED
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
  digitalWrite(16, HIGH);
  delay(300);
  digitalWrite(16, LOW);
  delay(300);
  digitalWrite(16, HIGH);
  delay(300);
  digitalWrite(16, LOW);
  delay(300);
  
}

void loop() 
{
//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS RX
/*
float Valor_Led = client.get(DEVICE, VARIABLE);
    
    if (Valor_Led != ERROR_VALUE)
    {
      //Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      //Serial.println(Valor_Led);
      
      if (Valor_Led==1)  
      {
        digitalWrite(16, HIGH);
      }
      if (Valor_Led==0)  
      {
        digitalWrite(16, LOW); 
      }  
    }

*/
  
//++++++++++++++++++++++++++++++++++++++++++++SENSOR HUMEDAD TIERRA
  int estado=digitalRead(5);
  if(estado==HIGH)
  {
    //Serial.println("seco ");
    ubidots.add("tierra",0);  // Change for your variable name
  }
  else 
  {
    //Serial.println("humedo ");
    ubidots.add("tierra",1);  // Change for your variable name
  }

//+++++++++++++++++++++++++++++++++++++++++++++++++UBIDOTS TX

  
  
  float value2 = 1024 - analogRead(A0);
  //float value3 = random(0, 9) * 100;
  
  ubidots.add("Luz", value2);
  //ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send("esp8266_principal");  // Will send data to a device label that matches the device Id

  if (bufferSent) 
  {
  digitalWrite(16, HIGH);
  delay(100);
  digitalWrite(16, LOW);
  delay(100);
  
  
    // Do something if values were sent properly
    //Serial.println("Values sent by the device");
  }

  delay(1000);
} 
