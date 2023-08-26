//http://www.esp8266learning.com/wemos-webserver-example.php



#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <math.h>
#include <Time.h>


const char* ssid = "INTERNET CNT";             //!!!!!!!!!!!!!!!!!!!!! modify this
const char* password = "cualeslaclave";                //!!!!!!!!!!!!!!!!!!!!!modify this
const int Rc = 10000; //valor de la resistencia
const int Vcc = 5;
const int SensorPIN = A0;
 
float A = 1.11492089e-3;
float B = 2.372075385e-4;
float C = 6.954079529e-8;
int centinela=0 ;
float K = 2.5; //factor de disipacion en mW/C

int ledPin = D4;          //connect led pin to d4 and ground
WiFiServer server(80);
 
void setup() {
  //Serial.begin(115200);
  Serial.begin(115200);
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

 
void loop() {

   
   
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
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
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  /*client.println("Hola Innacensa Led pin is now: ");
  if(value == HIGH) 
  {
    client.println("Off");  
  } else 
  {
    client.println("On");
  }*/
    
    float raw = analogRead(SensorPIN);
    float V =  raw / 1024 * Vcc;
    
    float R = (Rc * V ) / (Vcc - V);
    
    
    float logR  = log(R);
    float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );
    
    float kelvin = R_th - V*V/(K * R)*1000;
    float celsius = kelvin - 273.15;
    client.println("Temperatura[C]; ");
    client.println(celsius);  
    client.println(";");
  
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 4 OFF<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 4 ON<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}

