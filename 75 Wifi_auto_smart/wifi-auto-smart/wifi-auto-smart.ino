//http://www.esp8266learning.com/wemos-webserver-example.php



#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
int option=0;
int valvula1=1;
int valvula2=2;

const char* ssid = "INTERNET CNT";             //!!!!!!!!!!!!!!!!!!!!! modify this
const char* password = "cualeslaclave";                //!!!!!!!!!!!!!!!!!!!!!modify this
 
int ledPin = D4;          //connect led pin to d4 and ground
WiFiServer server(80);
 
void setup() {
  //Serial.begin(115200);
  Serial.begin(115200);
  delay(10);
   Serial.println("Hola car...");
  pinMode(valvula1,OUTPUT); 
  pinMode(valvula2,OUTPUT); 
 
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

  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(valvula1, LOW);
      delay(1000);
      digitalWrite(valvula1, HIGH);
      
      Serial.println("ok1");
      option=0;
    }
    if(option=='2') 
    {
      digitalWrite(valvula2, LOW);
      Serial.println("ok2");
      
      delay(1000);
      digitalWrite(valvula2, HIGH);
      option=0;
    }
  }  
   
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
 
  client.print("Hola Putito Led pin is now: ");
 
  if(value == HIGH) 
  {
    client.print("On");  
  } else 
  {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 4 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 4 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}

