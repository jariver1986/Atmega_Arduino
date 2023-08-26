//Declaración de variables globales y librerías
//#include <Dhcp.h>
//#include <Dns.h>
#include <Ethernet.h>
//#include <EthernetClient.h>
//#include <EthernetServer.h>
//#include <EthernetUdp.h>
#include <SPI.h>
int floatPin = 4; // se declara el pin de lectura del sensor de nivel
const int myRelee = 2;   // Declaramos la salida del relee
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 } ; //declaramos una MAC
EthernetClient client; //Instancia de cliente Ethernet
IPAddress ip(192, 168, 1, 177); //Conseguimos una ip, este valor puede cambiar dependiendo la red
char server[] = "www.server.com"; //Servidor, el valor cambia dependiendo el server
//--Fin

void setup() {
  // inicializamos el rele
  pinMode(myRelee, OUTPUT); //declaramos que es pin de salida
  // Preparamos el puerto serie
  Serial.begin(9600);
  pinMode (floatPin, INPUT);// declaramos que el pin sera de señal de entrada
  Serial.println("Sensor de nivel"); //imprimira mensaje
  beginConecction(); //Iniciamos la conexión de la placa
  delay(1000);//Esperamos un segundo
}


void loop() {
  //pregunta  si el sensor de nivel esta en estado bajo
  if ( analogRead (floatPin) == 0 )
  { //si cumple la condicion realiza el ciclo if
    Serial.println("Nivel de agua bajo");
    digitalWrite(myRelee, HIGH);// envia señal de alto al rele para encender bomba
    //Atrapamos la fecha, hora, minuto y segundo en el servidor para hacerlo más liviano al cliente arduino
    sendData("1");
  }
  //caso contrario ingresa a else
  else
  {
    digitalWrite(myRelee, LOW);// envia señal de bajo al rele para apagar la bomba
    //Atrapamos la fecha, hora, minuto y segundo en el servidor para hacerlo más liviano al cliente arduino
    sendData("0");
  }
  delay (1000); // Un pequeño retardo de 1 segundo.
}

//Método para iniciar conexión
void beginConecction() {
  //Preguntamos si podemos hacer una conexión con DHCP, si da error, conectamos con la ip y mac que tenemos
  //Aunque podriamos iniciar directamente
  Ethernet.begin(mac, ip);
}

boolean sendData(String data) {
  //Adjuntamos la MAC
  data = "actividad="+data;
  data += "&MAC=" + mac;
  Serial.println("Intentando conectar...");
  if (client.connect(server, 80) > 0) {
    Serial.println("Conectado");
    client.println("POST /app/ajax/registro.php HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    Serial.println("Datos enviados.");
    client.stop();
    return true;
  } else {
    Serial.println("Fallo en la conexión");
    return false;
  }
}




