//************************************************************
// this is a simple example that uses the painlessMesh library
//
// 1. sends a silly message to every node on the mesh at a random time between 1 and 5 seconds
// 2. prints anything it receives to Serial.print
//
//
//************************************************************
#include "UbidotsESPMQTT.h"
#include<SimpleDHT.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "painlessMesh.h"

#define   MESH_PREFIX     "Esperancito"
#define   MESH_PASSWORD   "1Corintios13"
#define   MESH_PORT       5555
#define TOKEN "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x" // Your Ubidots TOKEN cuenta John
#define WIFINAME "NETLIFE-RIVERA" //Your SSID
#define WIFIPASS "0909039109" // Your Wifi Pass

Ubidots client(TOKEN);
int contador=0;
int centinela=0;
int contador2=0;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  String msg = "Hello from node ";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  
    client.add("Node ", mesh.getNodeId()); //Insert your variable Labels and the value to be sent
    client.ubidotsPublish("Mesh");
    client.add("MSG", mesh.getNodeId());
    client.ubidotsPublish("Red");
    //client.loop();
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup() {
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() 
{
  // it will run the user scheduler as well
  mesh.update();
  if(!client.connected())
  {
      client.reconnect();
  }
  if((centinela==0)&&(contador2<10))
  {
    contador2++; 
  }
  else  {centinela=1;}
  
  // Publish values to 2 different data sources
  if((contador>90)||(centinela==0))
  {
    
    client.add("Node ", mesh.getNodeId()); //Insert your variable Labels and the value to be sent
    client.ubidotsPublish("Mesh");
    client.add("MSG",  mesh.getNodeId());
    client.ubidotsPublish("Red");
    client.loop();
//    Serial.println("Dato enviado a web temepratura: " + String(temperature));//Informacion a PC
  //  mySerialbt.println("_@"+String(temperature)+"@;");//Actualizo dato a BT
    contador=0;
  }
  contador++;
  delay(10000);
}
