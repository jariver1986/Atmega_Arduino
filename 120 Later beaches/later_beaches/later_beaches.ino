//172.22.64.1
//192.168.100.97
//tcp://localhost:1883
//usuario: ideTSer
//contraseña: secReTex4@m#

/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <AsyncMqttClient.h>
#include <ESPAsyncTCP.h>
#include<ESP8266WIFI.h>
#include<SimpleDHT.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// Update these with values suitable for your network.

//const char* ssid = "NETLIFE-RIVERA_EXT";
const char* ssid = "NETLIFE-RIVERA";
const char* password = "0909039109";
//const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* mqtt_server = "192.168.100.97";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[300];
//String msg;
int value = 0;


int pinDHT11 = 14;
SimpleDHT11 dht11(pinDHT11);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if (client.connect(clientId.c_str())) {
    if (client.connect(clientId.c_str(),"ideTSer","secReTex4@m#")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //client.setCredentials("ideTSer","secReTex4@m#");
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  byte data[40] = {0};
 
  float decimal=0.0;
  decimal=(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]);
  float dato= mlx.readObjectTempC();//temperature+decimal/10;
  //Serial.print("T = ");
  //Serial.println(mlx.readObjectTempC());
  
  Serial.print("temperatura: ");
  Serial.print(String(temperature));
  Serial.print(" C, ");
  Serial.print("Humedad: ");
  Serial.print((int)humidity); 
  Serial.println(" H");
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
     //snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
     
                                  //mac#2013-02-15#13:02:16.100#{ "modelo":"SJOHN", "sensores":[ { "nombre": "temperatura", "valor":"25", "unidadMedicion":"C" }, { "nombre": "voltaje", "valor":"225", "unidadMedicion":"V" } ] }
    //Char parte1[100]=""; //"#2013-02-15#13:02:16.100#{ \"modelo":"SR088", "sensores\":[ { \"nombre": "temperatura", "valor":"25", "unidadMedicion":"C\" ";
    snprintf (msg, 300,"84:F3:EB:9F:67:B3#2013-02-15#13:02:16.100#{ \"modelo\":\"JavaJOHN\", \"sensores\":[ { \"nombre\": \"Temperatura\", \"valor\":\"%1d\", \"unidadMedicion\":\"Centigrados\" }, { \"nombre\": \"humedad\", \"valor\":\"%1d\", \"unidadMedicion\":\"%\" } ] }",temperature,humidity);
    
    client.publish("topicPrincipal", msg);
    Serial.print("Publish message: ");
    Serial.println(msg);

    //Serial.print("mac : ");
    //Serial.println(WiFi.macAddress());
  }
}
