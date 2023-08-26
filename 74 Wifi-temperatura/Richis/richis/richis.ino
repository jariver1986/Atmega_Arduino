#include <ESP8266WiFi.h>
 
//const char* ssid     = "INTERNET CNT";   //replace with your own SSID
//const char* password = "cualeslaclave";    //replace with your own password
const char* ssid     = "INNACENSA";   //replace with your own SSID
const char* password = "innacensa.";    //replace with your own password
//const char* ssid     = "Movil";   //replace with your own SSID
//const char* password = "wilmerjv";    //replace with your own password

const char* host = "api.pushingbox.com";  
 
int button = 4;
double data;
int contador=0;

const int Rc = 10000; //valor de la resistencia
const int Vcc = 5;
const int SensorPIN = A0; 
float A = 1.11492089e-3;
float B = 2.372075385e-4;
float C = 6.954079529e-8;
int centinela=0 ;
float K = 2.5; //factor de disipacion en mW/C

 
void setup() 
{
  Serial.begin(115200);
  Serial.print("MAC:");
  Serial.println(WiFi.macAddress());
  delay(10);
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  pinMode(A0, INPUT);
  pinMode(button, INPUT);
}
 
void loop() 
{
 //if(digitalRead(button) == 0)
 //{
      contador=contador+1;
      float raw = analogRead(SensorPIN);
      float V =  raw / 1024 * Vcc;
      float R = (Rc * V ) / (Vcc - V);
      float logR  = log(R);
      float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );
      float kelvin = R_th - V*V/(K * R)*1000;
      float celsius = kelvin - 273.15;
    
      data = celsius;
      Serial.print("connecting to ");
      Serial.println(host);
    
      // Use WiFiClient class to create TCP connections
      WiFiClient client;
      const int httpPort = 80;
      if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
      }
     
      // We now create a URI for the request
      String url = "/pushingbox?";
      url += "devid=";
      url += "v62C14AF43323E30";//Proyecto1
      //url += "v50E6F9BA6BA4155";
      //url += "&data="+String(data)+","+String(contador)+",Nevera_pequena,Temperatura,3";
      url += "&data="+String(data)+","+String(contador)+",Nevera_grande,Temperatura,3";
      Serial.print("Requesting URL: ");
      Serial.println(url);
    
      // This will send the request to the server
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
      unsigned long timeout = millis();
      while (client.available() == 0) {
        if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
      Serial.print("Data Sent!");
    }
    //delay(1800000);
    delay(10000);
    Serial.println();
    Serial.println("closing connection");
  //}
}
