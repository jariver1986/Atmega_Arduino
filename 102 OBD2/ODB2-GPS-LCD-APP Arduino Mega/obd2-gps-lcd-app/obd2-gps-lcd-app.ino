#include <SoftwareSerial.h>
#include "ELMduino.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TinyGPS.h>
#include <String.h>

TinyGPS gps;
SoftwareSerial serialgps(4,3);  // RX, TX
SoftwareSerial mySerial(10,11); // RX, TX HC05
LiquidCrystal_I2C lcd(0x27,20,4);

//gsm
SoftwareSerial SIM900(7, 8);    // RX, TX GSM
//gsm

#define ELM_PORT mySerial
ELM327 myELM327;
char dato=' '; //Datos de gps
uint32_t rpm=0;
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
String lon;
void setup()
{
#if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif

  Serial.begin(115200);
  Serial2.begin(115200);
  ELM_PORT.begin(38400); //HC05
  Serial1.begin(9600);  //HC06
  serialgps.begin(9600);//GPS
  pinMode(sensor, INPUT); //Sensor declarado como entrada
  if (!myELM327.begin(ELM_PORT))
  {
    Serial.println("Couldn't connect to OBD scanner");
    while (1);
  }
  Serial.println("Connected to ELM327");
  
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
 ///////////////////////////////////////ODB2
  float tempRPM = myELM327.rpm();
  if (myELM327.status == ELM_SUCCESS)
  {
    rpm = (uint32_t)tempRPM;
  }
  Serial.println("ODB2 ARDUINO"); //ENVIO DE RPM POR PUERTO COM
  Serial.print("RPM: ");  //ENVIO DE RPM POR PUERTO COM
  Serial.println(rpm);    //ENVIO DE RPM POR PUERTO COM
  Serial1.println("_"+String(lon)+"@"+String(rpm)+";_"); // ENVIO DE DATOS A LA APP       
  
  
  
  lcd.clear();   //PRESENTACION DE DATOS EN LCD  
  
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  lcd.setCursor(10, 0); 
  lcd.print(rpm);
  lcd.setCursor(0, 1);
  
//SENSOR DE INTRUSO
  int ValSensor = digitalRead(sensor); //Guarda los valores obtenidos por el sensor

  if(ValSensor == 0)
  {
   lcd.print("ALERTA INTRUSO");
   conteo++;
   if(conteo>=2)
   {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LLAMADA");
//gsm      
      Serial.println("Llamada");
      DialVoiceCall(); //Hace llamado a funcion
      delay(2000); //Tiempo de retardo
      lcd.setCursor(0, 1);
      lcd.print("MENSAJE");
      Serial.println("Mensaje de alerta enviado");
      MensajeAlerta(); //Hace llamado a funcion
//gsm
      lcd.clear();
      conteo=0;
    }
  }
  else
  {
   lcd.print("SEGURIDAD OK");
  }
/////////////////////////////////////RETARDO IMPORTANTE PARA COORDINACION DE LECTURAS
  delay(2500);
/////////////////////////////////////GPS
  if (Serial2.available()) 
  { 
    
    datogps=Serial2.readStringUntil('@'); //RECEPCION DE ARDUINO ESCLAVO
    
    lcd.clear();               //PRESENTACION DE DATOS DE LATITUD
    lcd.setCursor(0, 0); 
    lcd.print("Lat:");
    lcd.setCursor(0, 1); 
    lcd.print("Lon:");
    lcd.setCursor(8, 0); lcd.print(datogps[2]);
    lcd.setCursor(9, 0); lcd.print(datogps[3]);
    lcd.setCursor(10, 0); lcd.print(datogps[4]);
    lcd.setCursor(11, 0); lcd.print(datogps[5]);
    lcd.setCursor(12, 0); lcd.print(datogps[6]);
    lcd.setCursor(13, 0); lcd.print(datogps[7]);
    lcd.setCursor(14, 0); lcd.print(datogps[8]);
    lcd.setCursor(15, 0); lcd.print(datogps[9]);
    
    
    lcd.setCursor(8, 1); lcd.print(datogps[10]); //PRESENTACION DE DATOS DE LONGITUD
    lcd.setCursor(9, 1); lcd.print(datogps[11]);
    lcd.setCursor(10, 1); lcd.print(datogps[12]);
    lcd.setCursor(11, 1); lcd.print(datogps[13]);
    lcd.setCursor(12, 1); lcd.print(datogps[14]);
    lcd.setCursor(13, 1); lcd.print(datogps[15]);
    lcd.setCursor(14, 1); lcd.print(datogps[16]);
    lcd.setCursor(15, 1); lcd.print(datogps[17]);
    

    
    Serial.print("GPS Latitud: "+String(datogps[2])+String(datogps[3])+String(datogps[4])
    +String(datogps[5])+String(datogps[6])+String(datogps[7])+String(datogps[8])+String(datogps[9]));  //ENVIOS POR PUERTO COM DATOS DE GPS
    Serial.println();
    Serial.print("GPS Longitud: "+String(datogps[10])+String(datogps[11])+String(datogps[12])+String(datogps[13])
  +String(datogps[14])+String(datogps[15])+String(datogps[16])+String(datogps[17]));  //ENVIOS POR PUERTO COM DATOS DE GPS
    Serial.println();
    
  }
  // Union de caracteres de longitug y latitud
  lon = String(datogps[2])+String(datogps[3]+String(datogps[4])
  +String(datogps[5])+String(datogps[6])+String(datogps[7])+String(datogps[8])+String(datogps[9])
  +"@"+String(datogps[10])+String(datogps[11])+String(datogps[12])+String(datogps[13])
  +String(datogps[14])+String(datogps[15])+String(datogps[16])+String(datogps[17])
  );
  //lon="7777777777777777";
  Serial.print("APP: ");
  Serial.println("_"+String(lon)+"@"+String(rpm)+";_"); // ENVIO DE DATOS A LA APP        
  Serial1.println("_"+String(lon)+"@"+String(rpm)+";_"); // ENVIO DE DATOS A LA APP       
  Serial.println();
  delay(2500);
}
