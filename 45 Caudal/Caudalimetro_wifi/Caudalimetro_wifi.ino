#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
/*Proceso
 * Nano resetea
 * presionar boton abrir valvula(lee internamente dato)
 * Nano espera por X de cerrar
 *Nano envia serial de info
 *wemos recibe y espera por cerradura de valvula para presentar datos
 *nano resetea wemos despues de recibir Q cinco segundos despues
 
 
 */
const char* ssid = "INTERNET CNT";             //!!!!!!!!!!!!!!!!!!!!! modify this
const char* password = "cualeslaclave";                //!!!!!!!!!!!!!!!!!!!!!modify this
 
int ledPin = D4;          //connect led pin to d4 and ground
WiFiServer server(80);

int incomingByte = 0;  
String chaine = "";
char fromSerial;
 
void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

 
void loop() 
{
 if (Serial.available() > 0) 
  {
    incomingByte = Serial.read();

    fromSerial = incomingByte;
    if (fromSerial != 10) 
    {
      chaine = chaine + fromSerial;
    }
  }
  
   
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
 
  // Wait until the client sends some data
  //Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  //Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
    Serial.print("X");
  }
  if (request.indexOf("/Reset") != -1){
    Serial.print("Q");
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

 
 
  

  
  client.print("Valvula esta: ");
  if(value == HIGH) 
  {
    client.print("On");
    
      
  } else 
  {
    client.print("Off ");
    client.println("<br>Resultados:");
    client.println("<br>"+String(chaine));
    String chaine = "";
    fromSerial=0;
    
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> Abrir valvula<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> Cerrar valvula<br>");
  client.println("Click <a href=\"/Reset\">here</a> Reset <br>");
  client.println("<br><br>");
  client.println("</html>");
  
 
  delay(1);
  //Serial.println("Client disconnected");
  Serial.println("");
 
}

