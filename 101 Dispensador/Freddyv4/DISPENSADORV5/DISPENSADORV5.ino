#include <Adafruit_MLX90614.h>
#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>
Adafruit_MLX90614 termometroIR = Adafruit_MLX90614();
int distancia1=0;
int distancia2=0;
int rele1=40;
int rele2=42;
//SoftwareSerial miBT(10,11);// PARA inicializar el bluetooh
Servo control1;
int bandera1=0;
int bandera2=0;
int bandera3=0;
int i=1;
int i2=0;
int TRIG1 = 22;
int ECO1= 24;
int TRIG2 = 26;
int ECO2= 28;
int pos0=30;
int pos1=31;
int pos2=32;
float temperaturaAmbiente=0;
float temperaturaObjeto=0;
int mano=0;
char blue=0;
float TEMPPRUEBA=0;
int cont=0;
int p1=0;
int p2=0;
int p3=0;
int p4=0;
int contador =0;//avisa si no hay recepcion por parte de BT
int dato=0;
int contador2 =0;
int pruebas=1000;
void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    termometroIR.begin(); // Iniciar termómetro infrarrojo con Arduino
    pinMode(2, OUTPUT); // servo
    //pinMode(38, INPUT); // sensor infarrojo
    pinMode(TRIG1, OUTPUT);
    pinMode(ECO1, INPUT);
    pinMode(TRIG2, OUTPUT);
    pinMode(ECO2, INPUT);
    pinMode(pos0, OUTPUT);
    pinMode(pos1, OUTPUT);
    pinMode(pos2, OUTPUT);
    pinMode(38,INPUT_PULLUP);
    pinMode(rele1, OUTPUT);
    pinMode(rele2, OUTPUT);
    //digitalWrite(38, LOW);
    digitalWrite(rele2, HIGH);
    Wire.begin();// comunicacion I2C
    control1.attach(2);
    control1.write(60);
    //miBT.begin(38400);// velocidad de comunicacion del bluetooh
    delay(500);
}
//esta funcion es para medir distancia
int medirdistancia (int TRIG, int ECO)
{
  int DURACION = 0;
  int DISTANCIA = 0;
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  DURACION = pulseIn(ECO, HIGH);
  DISTANCIA= DURACION / 58.2;
  delay(200);
  return DISTANCIA;
}

//esta funcion es para detectar persona en un rango de 1mt
int medirdistancia2 (int TRIG, int ECO)
{
int DURACION1 = 0;
int DISTANCIA1 = 0;
int rev1=0;
nuevo:
digitalWrite(TRIG, HIGH);
delay(1);
digitalWrite(TRIG, LOW);
DURACION1 = pulseIn(ECO, HIGH);
DISTANCIA1= DURACION1 / 58.2;
delay(200);
if (DISTANCIA1 > 100  || DISTANCIA1< 0 )
{
  goto nuevo;
}return DISTANCIA1;
}
//procedimiento para repartir gel
void repartirgel()
{
int revisar=0;
int cont2=0;
delay(250);
Serial.println("gel");
do{
Serial1.println("l@----;-");  
delay(250);
if(Serial1.available())
blue=Serial1.read();
delay(250);
}while(blue!='L');
do {  
digitalWrite(pos0, LOW);
digitalWrite(pos1, HIGH);
digitalWrite(pos2, HIGH);  
revisar=medirdistancia(TRIG1, ECO1);
 Serial.println(revisar);
 if (digitalRead(38) == HIGH && revisar < 50)//sirve para detectar la mano en el dispensador mediante el sensor de movimiento
{
Serial.println("REPARTIENDO");  
delay(250);
control1.write(0);
delay(400);
control1.write(60);
delay(400);
control1.write(0);
delay(400);
control1.write(60);
delay(400);
goto fin;  
}
delay(100);
cont2++;
if (cont2==50)
{
do{
Serial1.println("l@----;-");  
delay(250);
if(Serial1.available())
blue=Serial1.read();
delay(250);
}while(blue!='L');//vuelve a repetir durante 5 segundo que de la mano
cont2=0;  
}
}while(revisar < 50);
revisar=medirdistancia(TRIG1, ECO1);
Serial.println("mira sali");
delay(250); 
Serial.println(revisar); 
fin:
Serial1.println("m@----;-");// apagando mano en el dispensador
delay(250);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////INICIO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////INICIO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////INICIO
void loop() 
{
  /*
digitalWrite(rele2, HIGH);//prendo y apagao reles para las luces
digitalWrite(rele1, LOW);
delay(1000);
digitalWrite(rele1, HIGH);  
delay(1000);
digitalWrite(rele1, LOW);
delay(1000);
digitalWrite(pos0, HIGH);
digitalWrite(pos1, LOW);
digitalWrite(pos2, LOW);
Serial.println("listo");
*/
/////////////////////////////////////////////////Lectura ultrasonico persona
J:
contador2=0;
distancia1=medirdistancia(TRIG1, ECO1);
delay(100);
Serial.println("ENCENDIENDO"+ String(distancia1));
do{
  distancia1=medirdistancia(TRIG1, ECO1);
  delay(250);
  contador2++;
  if (contador2>40)
  {
    contador2=0; 
    Serial.println("FONDO NEGRO");
    goto fondonegro; 
    
   }
  }while(distancia1>20);//para encender el equipo, con este me sercioro que todo este listo antes de conectar al bluetooh
Serial.println("ARDUINO DETECTA");

//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR DE IMAGEN A(COVID)
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      iMAGEN H(CARGANDO)
do
{
  //eliminar abajo
  distancia1=medirdistancia(TRIG1, ECO1);
delay(100);
Serial.println("DISTANCIA = "+ String(distancia1));
//eliminar arriba
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("h@----;-");  //IMAGEN DE CARGANDO
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="H"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='H');
blue=0;
delay(3000); //retardo de imagen cargando

//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR DE IMAGEN H(CARGANDO)
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      iMAGEN B(COLOCAR MANO EN SENSOR)
do
{
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("b@----;-");  //IMAGEN DE CARGANDO
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="B"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='B');
blue=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA DETECTAR MANO EN SENSOR ULTRA2
//////////////////////////////////////////////////////////////////////////////////////////////////////////
contador2=0;
Serial.println("COLOCAR MANO");
do{
  distancia1=medirdistancia(TRIG2, ECO2);
  delay(250);
  contador2++;
  if (contador2>20)
  {
    contador2=0; 
    Serial.println("USUARIO SE FUE");
    goto fin; 
  }
  }while(distancia1>20);//
Serial.println("MANO DETECTADA");
delay(2000); //Retardo importante para evitar el montaje de audios.
//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR DE IMAGEN B(COLOCAR MANO EN SENSOR)
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      iMAGEN C(MIDIENDO TEMPERATURA)
do
{
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("c@----;-");  //IMAGEN DE MIDIENDO TEMEPRATURA
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="C"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='C');
blue=0;




//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA MEDIR TEMPERATURA y variable de transporte
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      
delay(3000);
pruebas++;
//int temp=pruebas;

float temp = 37.1;
if (temp>=38)
{ 
  goto grave;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR DE IMAGEN C(MIDIENDO TEMPERATURA)
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      IMAGEN D(IMAGEN TEMP OK)
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      IMAGEN E(IMAGEN TEMP NG)
do
{
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("d@"+String(pruebas)+";-");  //VALOR DE TEMPERATURA
    //Serial1.print("d@----;-");  //VALOR DE TEMPERATURA
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="D"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='D');
blue=0;
goto gel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
grave:
do
{
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("e@"+String(temp)+";-");  //VALOR DE TEMPERATURA
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="E"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='E');
blue=0;

goto fin;
/////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR DE IMAGEN D(IMAGEN TEMP OK)
/////////////////////////////////////////////////////////////////////////////////////////                      IMAGEN F(PONER LA MANO EN DISPENSADOR "TOMAR GEL")
gel:
delay(2000);//Retardo importante para evitar montaje de audios
do
{
  if ((contador == 0)||(contador>=14))
  {
    
    Serial1.print("f@"+String(temp)+";-");  //VALOR DE TEMPERATURA
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="F"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='F');
blue=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA DETECTAR MANO y DISPENSAR GEL
//////////////////////////////////////////////////////////////////////////////////////////////////////////                      

Serial.println("REPARTIENDO GEL");  
delay(4000);

/////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR DE IMAGEN F(PONER LA MANO EN DISPENSADOR "TOMAR GEL")
/////////////////////////////////////////////////////////////////////////////////////////                      IMAGEN G(GRACIAS)

do
{
  if ((contador == 0)||(contador>=14))
  {
    
    Serial1.print("g@"+String(temp)+";-");  //VALOR DE TEMPERATURA
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="G"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='G');
blue=0;


/////////////////////////////////////////////////////////////////////////////////////////PROCESO PARA PASAR A IMAGEN DE INICIO 
/////////////////////////////////////////////////////////////////////////////////////////                     

fin:
delay(3000);
do
{
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("a@----;-");  //VALOR DE TEMPERATURA
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="A"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='A');
blue=0;
Serial.println("IMAGEN DE INICIO");

goto J;
/////////////////////////////////////////////////////////////////////////////////////////////////////////IMAGEN DE FONDO NEGRO despues de 10 seg
fondonegro:

do
{
  if ((contador == 0)||(contador>=14))
  {
    Serial1.print("i@----;-");  //IMAGEN DE CARGANDO
    Serial.println("ARD PD IMAG");  //
    delay(50);
  }
  contador++;
  delay(100);
  if(Serial1.available())
  {
    blue=Serial1.read();
    delay(50);
    Serial.println("ARD RX = "+String(blue)); 
    delay(50);
    Serial.println("CONT = "+String(contador));  
    delay(50);
    if(blue=="I"){contador=1;}
  }  
  if (contador>14)
  {
   contador=1;  
   Serial.println("OUT");
   delay(100);
  }
}while(blue!='I');
blue=0;

goto J;

}
