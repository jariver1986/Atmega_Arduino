/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include <LiquidCrystal_I2C.h> //Libreria para control de LCD
#include <Wire.h>           //Libreria complemento para control de protocolo i2C
#include <String.h>  
#include <SoftwareSerial.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-NZwQEISNaqYauGjNNQMWmGLAS88g6Q"   // Token Empagran
//#define TOKEN "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x" // Your Ubidots TOKEN jariver86
#define WIFINAME "NETLIFE-RIVERA" //Your SSID
#define WIFIPASS "0909039109" // Your Wifi Pass
//#define WIFINAME "PLATAFORMA" //Your SSID
//#define WIFIPASS "HG_PLATAFORMAS_$00" // Your Wifi Pass

Ubidots client(TOKEN);
LiquidCrystal_I2C lcd(0x27,20,4); // LCD
SoftwareSerial mySerialnode(13,15); // RX, TX Serial Node remapeado

String datogps="0000000000000000";   
int year;
byte month,day,hour,minute,second, hundredths;
int ds = -77;
String incomingString="";
int contador=0;
int contador2=0;
float valor=0;
float valornocero=0;
/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerialnode.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);

  /////lcd
  lcd.init();
  lcd.backlight();
  //Display Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("IoT");
  lcd.setCursor(0, 1);
  lcd.print("Bienvenido");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO.");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO..");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO...");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO....");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Asistentes:");
  lcd.setCursor(10, 1); 
  lcd.print(ds);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }

  //RX de Nano
  if (mySerialnode.available() > 0) 
  {
    // read the incoming string:
    incomingString = mySerialnode.readStringUntil('@');
    datogps=incomingString;
    // prints the received data
    Serial.print("He recibido: ");
    Serial.println(incomingString);
    
    lcd.setCursor(0, 0);
    lcd.print("Asistentes:");
      contador++;
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Asistentes:");
      lcd.setCursor(0, 1);
      lcd.print(incomingString);

    valor = incomingString.toFloat();
    if(valor!=0)
    {
      valornocero = valor;  
    }
     //valor = incomingString.toInt();
     
   // if((contador2>90)||(contador2==0)) // cada 15 minutos
   // {
      contador2=0;
      client.add("Asistentes", valornocero); //Insert your variable Labels and the value to be sent
      client.ubidotsPublish("Empagran");
      //client.add("stuff", contador);
      //client.add("more-stuff", 120.2);
      //client.ubidotsPublish("Fuente2");
      client.loop();
    //} 
  }
  contador2++;
  delay(1500);
  }
