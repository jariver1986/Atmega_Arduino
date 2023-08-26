#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8);
int option=0;
void setup()
{
  Serial.begin(9600);             // we agree to talk fast!
  delay(20000);  // Espera 30 segundos mientras realiza la llamada 
}

void mensaje()
{
  //Serial.println("Enviando SMS...");
  Serial.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000);
  Serial.println("AT+CMGS=\"0993651746\""); //Numero al que vamos a enviar el mensaje
  delay(1000);
  Serial.println("Hola miwito estoy probando GSM");// Texto del SMS
  delay(100);
  Serial.println((char)26);//Comando de finalizacion ^Z
  delay(100);
  Serial.println();
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  //Serial.println("SMS enviado");
}
void llamar()
   {
      Serial.println("AT");  //Comando AT para realizar una llamada
      delay(3000);
      Serial.println("ATD043092223;");  //Comando AT para realizar una llamada
      delay(10000);  // Espera 30 segundos mientras realiza la llamada
      Serial.println("ATH");  // Cuelga la llamada
      delay(3000);
      
   }



void loop()
{
    if (Serial.available()>0)
    {
      option=Serial.read();
      if(option=='1') 
      {
        llamar();
      }
      if(option=='2') 
      {
        mensaje();
      }
    
    
     }
}



