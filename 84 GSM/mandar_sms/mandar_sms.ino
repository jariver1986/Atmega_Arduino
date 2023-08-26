#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // Configura el puerto serial para el SIM900

void setup()
{
  SIM900.begin(19200); //Configura velocidad del puerto serie para el SIM900
  Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  Serial.println("OK");
  delay (1000);
  SIM900.println("AT+CPIN=\"1867\""); //Comando AT para introducir el PIN de la tarjeta
  delay(25000); //Tiempo para que encuentre una RED
}

void mensaje_sms()
{
  //Serial.println("Enviando SMS...");
  SIM900.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000);
  SIM900.println("AT+CMGS=\"XXXXXXXXX\""); //Numero al que vamos a enviar el mensaje
  delay(1000);
  SIM900.println("SMS enviado desde un Arduino. Saludos de prometec.");// Texto del SMS
  delay(100);
  SIM900.println((char)26);//Comando de finalizacion ^Z
  delay(100);
  SIM900.println();
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  //Serial.println("SMS enviado");
}
void llamar()
   {
      //Serial.println("Realizando llamada...");
      SIM900.println("ATD043092223;");  //Comando AT para realizar una llamada
      delay(10000);  // Espera 30 segundos mientras realiza la llamada
      SIM900.println("ATH");  // Cuelga la llamada
      delay(1000);
      //Serial.println("Llamada finalizada");
   }

void loop()
{
  mensaje_sms(); //Envia SMS
  while (1); // Espera por tiempo indefinido
}
