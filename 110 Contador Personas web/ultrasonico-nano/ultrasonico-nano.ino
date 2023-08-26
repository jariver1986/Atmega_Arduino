#include <Ultrasonic.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerialnode(2,3); // RX, TX PIN3 ENVIA A NODE
Ultrasonic ultrasonic(4, 5);//Trig,Echo
Ultrasonic ultrasonic2(8, 9);//Trig,Echo
SoftwareSerial mySerialbt(6,7); // RX, TX 

int dato=0;
int dato2=0;
int distancia=100;
int distancia2=100;
int contador=0;
int contador2=0;
int contador3=0;
int centinela=0;
void setup()
{
    Serial.begin(115200);   
    mySerialnode.begin(115200);
    // pin 11 sensor Temperatura  DHT11   
}

void loop()
{
    distancia = ultrasonic.read();
    distancia2 = ultrasonic2.read();
    delay(100);
    if((distancia<40)&&(centinela==0))
    {
      Serial.println("D1= "+String(distancia));
      centinela=1;
    }
    if((distancia2<40)&&(centinela==1))
    {
      contador++;
      Serial.println("D2= "+String(distancia2));
      Serial.println("Contador: "+String(contador)+"@");
      centinela=0;
    }
    if(centinela==1)
      {contador3++;}
    else 
      {contador3=0;}
      
    if(contador3>50)
      {
        centinela=0;
        Serial.println("No entro");
      }
    ///////////////////////////////Comunicacion PC
    if (Serial.available()>0)
    {
      dato=Serial.read();
      if(dato=='1')
      {   
        Serial.println(String(contador)+"@"); //PC test
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
      Serial.print("Contador: "+String(contador)+"@");//Actualizo dato a PC serial
      contador2=0;
    }
}


        
     
