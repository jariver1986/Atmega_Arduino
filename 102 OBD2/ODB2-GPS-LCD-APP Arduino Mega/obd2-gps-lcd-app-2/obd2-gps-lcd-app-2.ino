#include <SoftwareSerial.h> //Libreria para comunicacion serial
#include "ELMduino.h"       //Libreria para lectura de datos de ELM
#include <LiquidCrystal_I2C.h> //Libreria para control de LCD
#include <Wire.h>           //Libreria complemento para control de protocolo i2C
#include <TinyGPS.h>        //Libreria para control y lectura de GPS
#include <String.h>         //Libreria para manejo de cadena de caracteres

// Definiciones de asignaciones de variables
TinyGPS gps;// GPS
SoftwareSerial serialgps(4,3);  // RX, TX
SoftwareSerial mySerial(10,11); // RX, TX HC05
LiquidCrystal_I2C lcd(0x27,20,4); // LCD

//gsm
SoftwareSerial SIM900(7, 8);    // RX, TX GSM
//gsm

//variables en general
#define ELM_PORT mySerial
ELM327 myELM327;
char dato=' '; //Datos de gps
uint32_t rpm = 12345;
int year;
byte month,day,hour,minute,second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
String datogps="0000000000000000";    //RECEPCION DE ARDUINO ESCLAVO
int sensor = 2; //Sensor magnetico
//gsm
char incoming_char = 0; //Variable que guarda los caracteres que envia el 900
//gsm
int conteo=0;
float latitude, longitude; //variables de lon y lat
char c='_';
int turno1=0;
int turno2=0;
void setup()
{
#if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif

  Serial.begin(115200);  //Consola
  Serial2.begin(115200); //Consola
  ELM_PORT.begin(38400); //HC05
  Serial1.begin(9600);  //HC06
  serialgps.begin(9600);//GPS
  pinMode(sensor, INPUT); //Sensor declarado como entrada
  //if (!myELM327.begin(ELM_PORT))
  //{
   // Serial.println("Couldn't connect to OBD scanner");
    //while (1);
  //}
  //Serial.println("Connected to ELM327");
  pinMode(12, OUTPUT); //LUZ VERDE
  pinMode(13, OUTPUT); //LUZ ROJA
  digitalWrite(12, LOW);//LUZ VERDE
  digitalWrite(13, LOW);//LUZ ROJA
  Serial.println("Inicio");
  Serial.println("LCD");
  lcd.init();
  lcd.backlight();
  //Display Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("OBD2");
  lcd.setCursor(0, 1);
  lcd.print("Welcome");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  lcd.setCursor(10, 1); 
  lcd.print(rpm);
  
  //gsm
  inicializaSIM900(); //Inicializa comunicación con sim
  //gsm
}

//gsm
void inicializaSIM900(){
  SIM900.begin(19200); //Configura velocidad del puerto serie para el SIM900
  //Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  //Serial.println("OK"); //Muestra mensaje por pantalla
  delay(1000); //Tiempo para que encuentre una RED
  SIM900.println("AT+CPIN=\"1234\""); //Comando AT para introducir el PIN de la tarjeta
  delay(2000); //Tiempo de retardo
}
void MensajeAlerta(){ 
  //Serial.println("Enviando SMS..."); //Muestra mensaje por pantalla
  SIM900.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000); //Tiempo de retardo
  SIM900.println("AT+CMGS=\"59394230466\""); //Numero al que vamos a enviar el mensaje
  //SIM900.println("AT+CMGS=\"593992409136\"");
  delay(1000); //Tiempo de retardo
  SIM900.println("TU VEHICULO ESTA SIENDO ROBADO");// Texto del SMS
  SIM900.print("www.google.com");//Colocamos la url de google maps
  SIM900.println((char)26);//Comando de finalizacion
  delay(100); //Tiempo de retardo
  SIM900.println(); //Muestra mensaje por pantalla
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  //Serial.println("SMS enviado Exitosamente");
}

void DialVoiceCall(){
  //Serial.println("Llamando......."); //Muestra mensaje por pantalla
  SIM900.println("ATD+ +593994230466;"); //Declara el número a enviar sms
  //SIM900.println("ATD+ +593992409136;"); //Declara el número a enviar sms
  delay(20000);  // Espera 20 segundos mientras realiza la llamada
  SIM900.println("ATH");  // Cuelga la llamad
  delay(1000); //Tiempo de retardo
  //Serial.println("Llamada finalizada"); //Muestra mensaje por pantalla
  SIM900.println(); //Salto de línea
}
//gsm

void loop()
{
  digitalWrite(12, HIGH);  //;SISTEMA ENCENDIDO
  while(serialgps.available())
        {
            c=serialgps.read();
            Serial.print(c);  
            //if(gps.encode(c))
            //{
            //  gps.f_get_position(&latitude, &longitude);
              delay(50);
            //}
        }
  turno1++;
  if (turno1>25)
  {
     ///////////////////////////////////////ODB2 lectura de rpm
      float tempRPM = myELM327.rpm();
      if (myELM327.status == ELM_SUCCESS)
      {
        rpm = (uint32_t)tempRPM;
      }
      Serial.println("ODB2 ARDUINO"); //ENVIO DE RPM POR PUERTO COM
      Serial.print("RPM: ");  //ENVIO DE RPM POR PUERTO COM
      Serial.println(rpm);    //ENVIO DE RPM POR PUERTO COM
      
      
      
      lcd.clear();   //PRESENTACION DE DATOS EN LCD  RPM
      
      lcd.setCursor(0, 0); //ubicacion de cursos de LCD //Presentacion de mensaje
      lcd.print("RPM:");   //Presentacion de mensaje
      lcd.setCursor(10, 0);//ubicacion de cursos de LCD 
      lcd.print(rpm);     //Presentacion de mensaje
      lcd.setCursor(0, 1);//ubicacion de cursos de LCD
      
                    //SENSOR DE INTRUSO
      int ValSensor = digitalRead(sensor); //Guarda los valores obtenidos por el sensor
    
      if(ValSensor == 0)
      {
       lcd.print("ALERTA INTRUSO");
       digitalWrite(13, HIGH);  //;SISTEMA ALERTA ENCENDIDO
       conteo++;
       if(conteo>=2)
       {
          lcd.clear(); // encera pantalla LCD
          lcd.setCursor(0, 0);//ubicacion de cursos de LCD
          lcd.print("LLAMADA");
    //gsm      
          Serial.println("Llamada");
          DialVoiceCall(); //Hace llamado a funcion
          delay(2000); //Tiempo de retardo
          lcd.setCursor(0, 1);//ubicacion de cursos de LCD //Presentacion de mensaje
          lcd.print("MENSAJE");//ubicacion de cursos de LCD //Presentacion de mensaje
          Serial.println("Mensaje de alerta enviado");
          MensajeAlerta(); //Hace llamado a funcion
    //gsm
          lcd.clear(); //encera pantalla LCD
          conteo=0;
        }
      }
      else
      {
       lcd.print("SEGURIDAD OK");//ubicacion de cursos de LCD //Presentacion de mensaje
       digitalWrite(13, LOW); //;SISTEMA ALERTA APAGADO
      }
    /////////////////////////////////////RETARDO IMPORTANTE PARA COORDINACION DE LECTURAS
      delay(2500);        
    /////////////////////////////////////GPS
      Serial.print("GPS: ");
      //if(serialgps.available())
        //{
            //int c=serialgps.read(); //Lectura de GPS
            //if(gps.encode(c))
            //{
                //float latitude, longitude; //variables de lon y lat
                //gps.f_get_position(&latitude, &longitude);
                Serial.println("_"+String(latitude,5)+"@"+String(longitude,5)+"@"+String(rpm)+";_");//Envio serial de datos
                Serial1.println("_"+String(latitude,5)+"@"+String(longitude,5)+"@"+String(rpm)+";_");//Envio serial de datos
                /*Serial.print(latitude,5);  
                Serial.print("@=");  
                Serial.print(longitude,5);  
                Serial.println("=");  */
                //delay(5000);
                /////////////////////////////////////// LCD CON LONGITUD Y LATITUD
                lcd.clear(); // encera pantalla
                lcd.setCursor(0, 0);//ubicacion de cursos de LCD //Presentacion de mensaje
                lcd.print("Lat:");//ubicacion de cursos de LCD //Presentacion de mensaje
                lcd.setCursor(0, 1);//ubicacion de cursos de LCD //Presentacion de mensaje
                lcd.print("Lon:");//ubicacion de cursos de LCD //Presentacion de mensaje
          
                lcd.setCursor(6, 0);//ubicacion de cursos de LCD //Presentacion de mensaje
                lcd.print(latitude,5);//ubicacion de cursos de LCD //Presentacion de mensaje
                lcd.setCursor(6, 1);//ubicacion de cursos de LCD //Presentacion de mensaje
                lcd.print(longitude,5);//ubicacion de cursos de LCD //Presentacion de mensaje
          
    
    ///////////////////////////////////////
            //}
        //}
    
    
      
      //Serial.print("APP: ");
      //Serial.println("_"+String(lon)+"@"+String(rpm)+";_"); // ENVIO DE DATOS A LA APP        
      //Serial1.println("_"+String(lon)+"@"+String(rpm)+";_"); // ENVIO DE DATOS A LA APP       
      Serial.println();
      delay(2500);
      turno1=0;
  }
  //delay(100);
}
