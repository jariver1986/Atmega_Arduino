//Libreria para el GPS
#include <TinyGPS++.h>//Libreriás para la Sim 900
#include <SoftwareSerial.h>
#include <String.h>
SoftwareSerial GPS(4, 5);//Declaramos el pin 5tx y 3Rx
TinyGPSPlus gps;//Declaramos el objeto gps
SoftwareSerial SIM900(7, 8); //Declara los pines a la cual se encuentra conectada la sim900

char incoming_char = 0; //Variable que guarda los caracteres que envia el 900
int sensor = 2; //Sensor magnetico

float Latitud, Longitud; //Variables para almacenar la longitud y latitud del GPS

void setup() {
  inicializaSIM900(); //Inicializa comunicación con sim
  pinMode(sensor, INPUT); //Sensor declarado como salida
}

void inicializaSIM900(){
  SIM900.begin(19200); //Configura velocidad del puerto serie para el SIM900
  Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  GPS.begin(9600);//Iniciamos el puerto serie del gps
  Serial.println("OK"); //Muestra mensaje por pantalla
  delay(1000); //Tiempo para que encuentre una RED
  SIM900.println("AT+CPIN=\"1234\""); //Comando AT para introducir el PIN de la tarjeta
  delay(2000); //Tiempo de retardo
}

void loop() {
  LecturaGPS(); //Invoca a la funcion 
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
  SIM900.println("AT+CMGS=\"593994230466\""); //Numero al que vamos a enviar el mensaje
  delay(1000); //Tiempo de retardo
  SIM900.println("SMS de Alerta, robo de carro!!");// Texto del SMS
  SIM900.print("https://maps.google.com/maps?q=");//Colocamos la url de google maps
  
    SIM900.print(""); //INSERTAR
    SIM900.print(gps.location.lat(),6);//Obtemos los datos de latitud del módulo gps y se lo enviamos al módulo gsm
    SIM900.print("+");
    SIM900.print(gps.location.lng(),6);//Obtemos los datos de longitud del módulo gps y se lo enviamos al módulo gsm
    
  SIM900.println((char)26);//Comando de finalizacion ^Z
  delay(100); //Tiempo de retardo
  SIM900.println(); //Muestra mensaje por pantalla
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  Serial.println("SMS enviado");
}

void DialVoiceCall(){
  Serial.println("Llamando......."); //Muestra mensaje por pantalla
  SIM900.println("ATD+ +593994230466 ;"); //Declara el número a enviar sms
  delay(20000);  // Espera 30 segundos mientras realiza la llamada
  SIM900.println("ATH");  // Cuelga la llamad
  delay(1000); //Tiempo de retardo
  Serial.println("Llamada finalizada"); //Muestra mensaje por pantalla
  SIM900.println(); //Salto de línea
}

void LecturaGPS(){
    while(GPS.available() > 0)//Verificamos si el módulo gps está enviando datos
    gps.encode(GPS.read());//Y los leemos 
    Serial.print(gps.location.lat(),6);//Obtemos los datos de latitud del módulo gps y se lo enviamos al módulo gsm
    Serial.print("+");
    Serial.println(gps.location.lng(),6);
}
