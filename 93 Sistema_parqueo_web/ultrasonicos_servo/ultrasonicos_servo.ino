#include <Wire.h>
#include <OzOLED.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <SPI.h>
#include <MFRC522.h>
int cadena[10]={0,0,0,0,0,0,0,0,0,0};
int enable[10]={3,3,3,3,3,3,3,3,3,3};
int acumulador=0;
int distancia1=0;
int distancia2=0;
int distancia3=0;
int distancia4=0;
int distancia5=0;
int distancia6=0;
int distancia7=0;
int distancia8=0;
int distancia9=0;
int distancia10=0;

Ultrasonic ultrasonic1(5,6,23200); 
Ultrasonic ultrasonic2(7,8,23200); 
Ultrasonic ultrasonic3(34,35,23200);
Ultrasonic ultrasonic4(36,37,23200);
Ultrasonic ultrasonic5(22,23,23200);
Ultrasonic ultrasonic6(24,25,23200);
Ultrasonic ultrasonic7(26,27,23200);
Ultrasonic ultrasonic8(28,29,23200);
Ultrasonic ultrasonic9(30,31,23200);
Ultrasonic ultrasonic10(32,33,23200);

int option = 0;
int sonido = 2;
Servo miServo1;
Servo miServo2;
const int RST_PIN = 9;            // Pin 9 para el reset del RC522
const int SS_PIN = 53;            // Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crear instancia del MFRC522
 
String printArray(byte *buffer, byte bufferSize) {
  String resultado="";
   for (byte i = 0; i < bufferSize; i++) {
      //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      //Serial.print(buffer[i], HEX);
      //Serial.print(buffer[i], HEX);
      resultado+=String(buffer[i], HEX);
   }
   return resultado;
}
void setup(void)
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(sonido, OUTPUT);
  miServo1.attach(3);
  miServo2.attach(4);
  miServo1.write(90);
  miServo2.write(0);
  digitalWrite(sonido, LOW);
  //++++++++++++++++++++++++++++++
  OzOled.init();  //initialze SEEED OLED display
  OzOled.setNormalDisplay();
  //OzOled.setHorizontalMode(); 
  OzOled.clearDisplay();
  //OzOled.printString("SISTEMA PARQUEO");
  SPI.begin();         //Función que inicializa SPI
   mfrc522.PCD_Init();     //Función  que inicializa RFID
  delay(1000);
}

void alarma()
{

  digitalWrite(sonido, HIGH);
  delay(200);
  digitalWrite(sonido, LOW);
  delay(200);
  
}

String imprime()
{
  String data="@";
     // Serial.print("@");
      for(int i=0;i<10;i++)
      {
        data+=cadena[i];
        //Serial.print(cadena[i]);
        if(i<9) 
        {
          //Serial.print(";");
          data+=";";
          }
      };
      //Serial.println("@");
      data+="@";
      return data;
  }
String imprimeenable()
{
  String data="#";
     // Serial.print("#");
      for(int i=0;i<10;i++)
      {
        data+=enable[i];
        //Serial.print(enable[i]);
        if(i<9) 
        {
          //Serial.print(";");
          data+=";";
          }
      };
     // Serial.println("#");
     data+="#";
     return data;
  }
void lectura()
{
distancia1 = ultrasonic1.Ranging(CM);
delay(10);
distancia2 = ultrasonic2.Ranging(CM);
delay(10);
distancia3 = ultrasonic3.Ranging(CM);
delay(10);
distancia4 = ultrasonic4.Ranging(CM);
delay(10);
distancia5 = ultrasonic5.Ranging(CM);
delay(10);
distancia6 = ultrasonic6.Ranging(CM);
delay(10);
distancia7 = ultrasonic7.Ranging(CM);
delay(10);
distancia8 = ultrasonic8.Ranging(CM);
delay(10);
distancia9 = ultrasonic9.Ranging(CM);
delay(10);
distancia10 = ultrasonic10.Ranging(CM);
delay(10);
}
void loop(void)
{
  if (mfrc522.PICC_IsNewCardPresent())
   {
      if (mfrc522.PICC_ReadCardSerial())
      {
         //Serial.print(F("ID:"));
         String r=printArray(mfrc522.uid.uidByte, mfrc522.uid.size);
         //Serial.println();
         String enviar=r+"-"+r+"-"+r+"-"+r+"-"+r+"-"+r;
         Serial.println(enviar);
 
         // Finalizar lectura actual
         mfrc522.PICC_HaltA();
      }
   }
  if (Serial.available() > 0)
  {
    //leemos la opcion enviada
    option = Serial.read();
    if (option == '1')
    {
      miServo1.write(0);   delay(3000);      miServo1.write(90);      delay(3000);      option = 0;
    }
    if (option == '2')
    {
      miServo2.write(90);      delay(3000);      miServo2.write(0);      delay(3000);      option = 0;
    }
    if (option == '3')
    {
      alarma();      option = 0;
    }
    if (option == 'A') {enable[0]=3;  option = 0;}
    if (option == 'B') {enable[0]=4;  option = 0;}

    if (option == 'C') {enable[1]=3;  option = 0;}
    if (option == 'D') {enable[1]=4;  option = 0;}

    if (option == 'E') {enable[2]=3;  option = 0;}
    if (option == 'F') {enable[2]=4;  option = 0;}

    if (option == 'G') {enable[3]=3;  option = 0;}
    if (option == 'H') {enable[3]=4;  option = 0;}

    if (option == 'I') {enable[4]=3;  option = 0;}
    if (option == 'J') {enable[4]=4;  option = 0;}

    if (option == 'K') {enable[5]=3;  option = 0;}
    if (option == 'L') {enable[5]=4;  option = 0;}

    if (option == 'M') {enable[6]=3;  option = 0;}
    if (option == 'N') {enable[6]=4;  option = 0;}

    if (option == 'O') {enable[7]=3;  option = 0;}
    if (option == 'P') {enable[7]=4;  option = 0;}

    if (option == 'Q') {enable[8]=3;  option = 0;}
    if (option == 'R') {enable[8]=4;  option = 0;}

    if (option == 'S') {enable[9]=3;  option = 0;}
    if (option == 'T') {enable[9]=4;  option = 0;}
  }
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lectura();
        
    if(distancia1<10)  {cadena[0]=1;}  else      {cadena[0]=0;}
    if(distancia2<10)  {cadena[1]=1;}  else      {cadena[1]=0;}
    if(distancia3<10)  {cadena[2]=1;}  else      {cadena[2]=0;}
    if(distancia4<10)  {cadena[3]=1;}  else      {cadena[3]=0;}
    if(distancia5<10)  {cadena[4]=1;}  else      {cadena[4]=0;}
    if(distancia6<10)  {cadena[5]=1;}  else      {cadena[5]=0;}
    if(distancia7<10)  {cadena[6]=1;}  else      {cadena[6]=0;}
    if(distancia8<10)  {cadena[7]=1;}  else      {cadena[7]=0;}
    if(distancia9<10)  {cadena[8]=1;}  else      {cadena[8]=0;}
    if(distancia10<10)  {cadena[9]=1;}  else      {cadena[9]=0;}

    String datoEnviar=imprime();  
    
    //delay(1000);    
   datoEnviar+= imprimeenable();
   String env="%+"+datoEnviar+"+%";
   env+=env+env+env+env;
   Serial.println(env);
    if((distancia1<10)&&(enable[0]==4))   {alarma();    }  
    if((distancia2<10)&&(enable[1]==4))   {alarma();    }  
    if((distancia3<10)&&(enable[2]==4))   {alarma();    }  
    if((distancia4<10)&&(enable[3]==4))   {alarma();    }  
    if((distancia5<10)&&(enable[4]==4))   {alarma();    }  
    if((distancia6<10)&&(enable[5]==4))   {alarma();    }  
    if((distancia7<10)&&(enable[6]==4))   {alarma();    }  
    if((distancia8<10)&&(enable[7]==4))   {alarma();    }  
    if((distancia9<10)&&(enable[8]==4))   {alarma();    }  
    if((distancia10<10)&&(enable[9]==4))   {alarma();    }  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    acumulador = cadena[0]+cadena[1]+cadena[2]+cadena[3]+cadena[4]+cadena[5]+cadena[6]+cadena[7]+cadena[8]+cadena[9];
    OzOled.clearDisplay();
    if (acumulador==0)
    {OzOled.printString(" Lib:10 Ocup:00");}
    if (acumulador==1)
    {OzOled.printString(" Lib:09 Ocup:01");}
    if (acumulador==2)
    {OzOled.printString(" Lib:08 Ocup:02");}
    if (acumulador==3)
    {OzOled.printString(" Lib:07 Ocup:03");}
    if (acumulador==4)
    {OzOled.printString(" Lib:06 Ocup:04");}
    if (acumulador==5)
    {OzOled.printString(" Lib:05 Ocup:05");}
    if (acumulador==6)
    {OzOled.printString(" Lib:04 Ocup:06");}
    if (acumulador==7)
    {OzOled.printString(" Lib:03 Ocup:07");}
    if (acumulador==8)
    {OzOled.printString(" Lib:02 Ocup:08");}
    if (acumulador==9)
    {OzOled.printString(" Lib:01 Ocup:09");}
    if (acumulador==10)
    {OzOled.printString(" Lib:00 Ocup:10");}  
    delay(1000);    
}








