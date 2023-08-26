
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h> //Libreria para control de LCD
#include <Wire.h>  //Libreria complemento para control de protocolo i2C
SoftwareSerial mySerialnode(2,3); // RX, TX PIN3 ENVIA A NODE D3
//Ultrasonic ultrasonic(4, 5);//Trig,Echo
//Ultrasonic ultrasonic2(8, 9);//Trig,Echo
SoftwareSerial mySerialbt(6,7); // RX, TX 
LiquidCrystal_I2C lcd(0x27,20,4); // LCD
int dato=0;
int dato2=0;
int distancia=0;
int distancia2=0;
int contador=0;  //contador entradas
int contador2=0;
int contador3=0;
int contador4=0; // contador salida
int centinela=0;
int centinela2=0;
int pin10 = 4;
int pin11 = 5;

void setup()
{
    Serial.begin(115200);   
    mySerialnode.begin(115200);
    // pin 11 sensor Temperatura  DHT11 
    pinMode(pin10, INPUT);
    pinMode(pin11, INPUT);

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
  lcd.print("IN:");
  lcd.setCursor(10, 0); 
  lcd.print(contador);

  lcd.setCursor(0, 1);
  lcd.print("OUT");
  lcd.setCursor(10, 1); 
  lcd.print(contador4);
}

void loop()
{
    distancia  = digitalRead(pin10);  //lectura digital de pin10
    distancia2 = digitalRead(pin11);  //lectura digital de pin11
    delay(80);

    /////entrada
    if((distancia == HIGH)&&(centinela==0))
    {
      Serial.println("D1= "+String(distancia));
      centinela=1;
      
    }
    if((distancia2 == HIGH)&&(centinela==1)&&(distancia == LOW))
    {
      contador++;
      Serial.println("D2= "+String(distancia2));
      Serial.println("Contador entrada: "+String(contador)+"@");
      /////////LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("IN:");
      lcd.setCursor(10, 0); 
      lcd.print(contador);
    
      lcd.setCursor(0, 1);
      lcd.print("OUT");
      lcd.setCursor(10, 1); 
      lcd.print(contador4);
      centinela=0;
    }

    ///salida
    if((distancia2 == HIGH)&&(centinela2==0))
    {
      Serial.println("D2= "+String(distancia2));
      centinela2=1;
    }
    if((distancia == HIGH)&&(centinela2==1)&&(distancia2 == LOW))
    {
      contador4++;
      Serial.println("D1= "+String(distancia));
      Serial.println("Contador salida: "+String(contador4)+"@");
       /////////LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("IN:");
      lcd.setCursor(10, 0); 
      lcd.print(contador);
    
      lcd.setCursor(0, 1);
      lcd.print("OUT");
      lcd.setCursor(10, 1); 
      lcd.print(contador4);
     
      centinela2=0;
    }
    
    if((centinela==1)||(centinela2==1))
      {contador3++;}
    else 
      {contador3=0;}
      
    if(contador3>50)
      {
        centinela=0;
        centinela2=0;
        Serial.println("No entro");
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OBJETO:");
      delay(500);
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("IN:");
      lcd.setCursor(10, 0); 
      lcd.print(contador);
    
      lcd.setCursor(0, 1);
      lcd.print("OUT");
      lcd.setCursor(10, 1); 
      lcd.print(contador4);
      centinela=0;
      }
    ///////////////////////////////Comunicacion PC
    if (Serial.available()>0)
    {
      dato=Serial.read();
      if(dato=='1')
      {   
        Serial.println("Contador entrada:"+String(contador)+"@"); //PC test
        Serial.println("Contador salida :"+String(contador4)+"@"); //PC test
        mySerialnode.println(String(contador)+"@");//Actualizo dato a Node
      } 
      dato=0;
    }
    
    //Para pedir dato desde bluetooth APK
    if (mySerialbt.available()>0)
    {
      dato2=mySerialbt.read();
      if(dato2=='1')
      {
        mySerialbt.println("_@"+String(contador)+"@;");
        dato=0;
      }
    }
    contador2++;
    if(contador2>300)
    {
      mySerialnode.println(String(contador)+"@");//Actualizo dato a Node
      mySerialbt.println("_@"+String(contador)+"@;");//Actualizo dato a BT
      Serial.println("Contador entrada: "+String(contador)+"@");//Actualizo dato a PC serial
      Serial.println("Contador salida : "+String(contador4)+"@");//Actualizo dato a PC serial
      contador2=0;
    }
}


        
     
