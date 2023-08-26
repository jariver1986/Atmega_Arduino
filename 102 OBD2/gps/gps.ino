//Libreriás para la Sim 900
#include <SoftwareSerial.h>
#include <String.h>
//Objeto
SoftwareSerial SIM900(7, 8); //Declara los pines a la cual se encuentra conectada la sim900

char incoming_char = 0; //Variable que guarda los caracteres que envia el 900
int sensor = 2; //Sensor magnetico

void setup() {
  inicializaSIM900(); //Inicializa comunicación con sim
  pinMode(sensor, INPUT); //Sensor declarado como salida
}

void inicializaSIM900(){
  SIM900.begin(19200); //Configura velocidad del puerto serie para el SIM900
  Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  Serial.println("OK"); //Muestra mensaje por pantalla
  delay(1000); //Tiempo para que encuentre una RED
  SIM900.println("AT+CPIN=\"1234\""); //Comando AT para introducir el PIN de la tarjeta
  delay(2000); //Tiempo de retardo
}

void loop() {
  int ValSensor = digitalRead(sensor); //Guarda los valores obtenidos por el sensor

  if(ValSensor == 0){ //De ser correcta ingresa a la condicion
    DialVoiceCall(); //Hace llamado a funcion
    delay(2000); //Tiempo de retardo
   MensajeAlerta(); //Hace llamado a funcion
   Serial.println("Mensaje de alerta enviado"); //Muestra mensaje por pantalla
  }
  else if(ValSensor == 1){ //De ser correcta ingresa a la condicion
  Serial.println("Sin Novedad"); //Muestra mensaje por pantalla
  }
}

void MensajeAlerta(){ 
  Serial.println("Enviando SMS..."); //Muestra mensaje por pantalla
  SIM900.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000); //Tiempo de retardo
  SIM900.println("AT+CMGS=\"59394230466\""); //Numero al que vamos a enviar el mensaje
  delay(1000); //Tiempo de retardo
  SIM900.println("TU VEHICULO ESTA SIENDO ROBADO");// Texto del SMS
  SIM900.print("www.google.com");//Colocamos la url de google maps
  SIM900.println((char)26);//Comando de finalizacion
  delay(100); //Tiempo de retardo
  SIM900.println(); //Muestra mensaje por pantalla
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  Serial.println("SMS enviado Exitosamente");
}

void DialVoiceCall(){
  Serial.println("Llamando......."); //Muestra mensaje por pantalla
  SIM900.println("ATD+ +593994230466;"); //Declara el número a enviar sms
  delay(20000);  // Espera 20 segundos mientras realiza la llamada
  SIM900.println("ATH");  // Cuelga la llamad
  delay(1000); //Tiempo de retardo
  Serial.println("Llamada finalizada"); //Muestra mensaje por pantalla
  SIM900.println(); //Salto de línea
}
