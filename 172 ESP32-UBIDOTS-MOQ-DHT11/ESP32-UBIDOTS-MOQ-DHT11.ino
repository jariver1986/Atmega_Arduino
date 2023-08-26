/******************************************
 *
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************

/****************************************
 * Include Libraries
 ****************************************/
////////////////////////////////////////////////////UBIDOTS
#include "UbidotsEsp32Mqtt.h"
int cont=0;

///////////////////////////////////////////////////Promedio
#include <averager.h>
averager<int,28> voltage;
int co=0;
averager<int,28> temp;
int promediotemp=0;
averager<int,28> hum;
int promediohum=0;
 ////////////////////////////////////////////////////DHT11
#include <SimpleDHT.h>
int pinDHT11 = 21;
SimpleDHT11 dht11(pinDHT11);
float h;
float t;

/////////////////////////////////////////////////////Relay

int semaforoT=0;
int semaforoCO=0;
int semaforoH=0;

///////////////////////////////////////////////////////MOQ
#include <MQUnifiedsensor.h>
/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino MEGA")
#define         Pin                     (34)  //Analog input 3 of your arduino
/***********************Software Related Macros************************************/
#define         Type                    ("MQ-2") //MQ2
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm 

/*****************************Globals***********************************************/
MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
/*****************************Globals***********************************************/

/****************************************
 * Define Constants UBIDOTS
 ****************************************/ 
                              
const char *UBIDOTS_TOKEN = "BBFF-I14P1Pk3mVHkcuVwZM68ol2vQgGYG0";  // Put here your Ubidots TOKEN
//const char *UBIDOTS_TOKEN = "BBFF-Uwy4vl7oGuHe5EKmHsUgknC7AWiY2x";  // Put here your Ubidots TOKEN

const char *WIFI_SSID = "NETLIFE-RIVERA";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "0909039109";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "Dispositivo";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "Temperatura"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL2 = "Humedad"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL3 = "CO"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL4 = "ST"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL5 = "SH"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL6 = "SCO"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL7 = "R1"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL8 = "R2"; // Put here your Variable label to which data  will be published

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;

Ubidots ubidots(UBIDOTS_TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();

  //////////////////////////////////////////////////////////////////RELAY
  pinMode(5,OUTPUT);
  pinMode(18,OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(18, HIGH);

  //////////////////////////////////////////////////////////////////MOQ
  
  //Set math model to calculate the PPM concentration and the value of constants
  MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ2.setA(36974); MQ2.setB(-3.109); // Configure the equation to to calculate LPG concentration
  /*
    Exponential regression:
    Gas    | a      | b
    H2     | 987.99 | -2.162
    LPG    | 574.25 | -2.222
    CO     | 36974  | -3.109
    Alcohol| 3616.1 | -2.675
    Propane| 658.71 | -2.168
  */

  /*****************************  MQ Init ********************************************/ 
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ2.init(); 
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ2.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ2.calibrate(RatioMQ2CleanAir);
    Serial.print(".");
  }
  MQ2.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
  /*****************************  MQ CAlibration ********************************************/ 

  MQ2.serialDebug(true);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


void loop()
{
  ///////////////////////////////////////////////////DHT11
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print((int)temperature); Serial.print(" *C,  "); 
  Serial.print((int)humidity); Serial.print(" H,  ");

  t = temperature;
  h = humidity;

  
  ////////////////////////////////////////////////////MOQ
  
  MQ2.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  //MQ2.serialDebug(); // Will print the table on the serial port

  Serial.print(MQ2.readSensor()); Serial.println(" ppm ");

  ///////////////////////////////////////////////////////////////Promedios temperatura
  temp.append(t);
  promediotemp=temp.getAverage();
  Serial.print("t = ");
  Serial.print(promediotemp);

  ///////////////////////////////////////////////////////////////Promedios Humedad
  hum.append(h);
  promediohum=hum.getAverage();
  Serial.print("  h = ");
  Serial.print(promediohum);

  ///////////////////////////////////////////////////////////////Promedios MOQ
  if(MQ2.readSensor()<300)
  {  
    voltage.append(MQ2.readSensor());
    co = voltage.getAverage();
    Serial.print("  CO = ");
    Serial.println(co);
  }
  
  
  

  
    
  ////////////////////////////////////////////////////UBIDOTS
  if(cont>=30)
  {
        ////////////////////////////////////////////////////RELAY
    
      //validacion de temperatura
    
      if((t<30)||(co<9))
      {
        digitalWrite(5, LOW);
        digitalWrite(18, HIGH);
        
      }
      if(((t>=30)&&(t<=32))||((co>=9)&&(co<=35)))
      {
        digitalWrite(5, LOW);
        digitalWrite(18, HIGH);
      
      }
      if((t>32)||(co>35))
      {
        digitalWrite(5, HIGH);
        digitalWrite(18, LOW);  
      }

      if(t>32)
      {
        semaforoT=2;
      }
      if(co>35)
      {
        semaforoCO=2; 
      }

      if((t>=30)&&(t<=32))
      {
        
        semaforoT=1;
        
      }
      if((co>=9)&&(co<=35))
      {
        semaforoCO=1;
      }

      if(t<30)
      {
        semaforoT=0; 
      }
      if(co<9)
      {
        semaforoCO=0;
      }
    //////////////////////////////////////////////////////
      //Validacion de Humedad
      if(h<40)
      {
        semaforoH=0;
      }
      if((h>=40)&&(h<=60))
      {
        semaforoH=1;
      }
      if(h>60)
      {
        semaforoH=2;
      }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // put your main code here, to run repeatedly:
    if (!ubidots.connected())
    {
      ubidots.reconnect();
    }
    
    //float value = analogRead(analogPin);
    ubidots.add(VARIABLE_LABEL, promediotemp ); // Insert your variable Labels and the value to be sent
    ubidots.add(VARIABLE_LABEL2, promediohum );
    ubidots.add(VARIABLE_LABEL3, co );
    ubidots.add(VARIABLE_LABEL4, semaforoT );
    ubidots.add(VARIABLE_LABEL5, semaforoH );
    ubidots.add(VARIABLE_LABEL6, semaforoCO );
    //ubidots.add(VARIABLE_LABEL7, digitalRead(5) );
    //ubidots.add(VARIABLE_LABEL8, !digitalRead(18) );
    
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
    
    ubidots.loop();
  }
  if(cont>31) cont=0; 
  
  cont++;
  
  delay(1000);
}
