   //Librerias
#include <Wire.h>// un solo cable de comunicacion dht11
#include <SPI.h>//Protocolo de pueeto serial rtc, lcd presion
#include <Adafruit_BMP280.h>//sensor de presion
#include <LCD_I2C.h>//para lcd
#include "RTClib.h"//reloj
#include <SimpleDHT.h>//sensor de temperatura y humedad
#include <MQUnifiedsensor.h>//sensor MOQ
#include <SoftwareSerial.h>//Para GPS
#include <TinyGPS.h>//Complemento de GPS


//Asignaciones de objetos

//LCD_I2C lcd(0x27, 16, 2); // original Default address of most PCF8574 modules, change according
LCD_I2C lcd(0x27, 20, 4); // Default address of most PCF8574 modules, change according

////////////RTC
RTC_DS1307 RTC;     // Setup an instance of DS1307 naming it RTC

////////////Sensor de presion
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

///////////////////////DHT11
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

////////////////////////MQ2
//Include the library
#include <MQUnifiedsensor.h>
/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino MEGA")
#define         Pin                     (A0)  //Analog input 3 of your arduino
/***********************Software Related Macros************************************/
#define         Type                    ("MQ-2") //MQ2
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm 

/*****************************Globals***********************************************/
MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
int centinela=0;


/*****************************Variables Globales***********************************************/

////////////////////////////SENSOR UV

float sensorVoltage;   
float sensorValue;
int UV_index;
String quality ="";

///////////////////////////SENSOR DE LLUVIA
const int sensorPin = A2;

//////////////////////////RELAY
int relay1 = 3;
int relay2 = 4;

//////////////////////////LCD
int cont1=0;
int cont2=0;
//////////////////////////UBIDOTS
int cont3=0;
/////////////////////////GPS
TinyGPS gps;
SoftwareSerial serialgps(10,11); //RX,TX ARDUINO MEGA
float latitude=0.00000;
float longitude=0.00000;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  //////////////////////////////////////////////////////////////////////Comunicacion serial
  Serial.begin(115200); //Comunicacion serial con el computador
  Serial1.begin(115200);//Comunicacion serial con con ESP8266

  
  /////////////////////////////////////////////////////////////////////Sensor de presion
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();


  //////////////////////////////LCD
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    PROYECTO:"); // You can make spaces using well... spaces
  lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("    ESTACION"); // You can make spaces using well... spaces
  lcd.setCursor(0,2);
  lcd.print("    METEOROLOGICA"); // You can make spaces using well... spaces
  lcd.setCursor(0, 3); // Or setting the cursor in the desired position.
  lcd.print("Para: IngenieriaUCSG"); // You can make spaces using well... spaces
  delay(1000);

  
  //////////////////////////////RTC
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC
  //RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime

  //////////////////////////////MQ2
  
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
  MQ2.init(); 
  //Serial.print("Calibrating please wait.");
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

  /////////////////////////////////////////SENSOR DE LLUVIA

  //pinMode(sensorPin, INPUT);  //definir pin como entrada

  ////////////////////////////////////////RELAY
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  ///////////////////////////////////////GPS
  serialgps.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CARGANDO...");
  while((serialgps.available())&&(latitude==0)&&(longitude==0))
  {
    int c=serialgps.read();
    if(gps.encode(c))
    {
      gps.f_get_position(&latitude, &longitude);
      
    }
  }   
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void loop() 
{
  /////////////////////////////RTC
    DateTime now = RTC.now();

 /*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    */
    
  ///////////////////////////////////////////////SENSOR DE PRESION
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  /*Serial.print(F("Temperatura [*C]= "));
  Serial.println(temp_event.temperature);

  Serial.print(F("Presion [hPa]= "));
  Serial.println(pressure_event.pressure);

  Serial.print(F("Altura [m]= "));
  if(bmp.readAltitude(1013.25)>0)
  Serial.println(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! 
  //else
  //Serial.println("1.0000"); /* Adjusted to local forecast! 
  */
  
    /////////////////////////////DHT11 TEMPERATURA
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    //Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); 
    return;
  }
  //Serial.print("Temp cabina [*C]: ");
  //Serial.println((int)temperature); 
  //Serial.print("Humedad [%]: ");
  //Serial.println((int)humidity);

  //////////////////////////////MQ2 sensor de CO
  MQ2.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ2.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  //MQ2.serialDebug(); // Will print the table on the serial port
  //Serial.print("PPM CO: ");
  //Serial.print(MQ2.readSensor());
  //Serial.println();
  
  //////////////////////////////////////////SENSOR UV
  sensorValue   = analogRead(A1);
  sensorVoltage = sensorValue/1024*5.0;
  UV_index= sensorVoltage/0.1;
  //condition for UV state
  if(UV_index<=2){ 
   quality = "LOW";
   }

  else if(UV_index > 2 && UV_index <=5){
   quality = "MOD";
   }

  else if(UV_index>5 && UV_index<=7){
   quality = "HIGH";
   }

  else if(UV_index>7 && UV_index<=10){
   quality = "VERY HIGH";

   }

  else{
   quality = "EXTREME";
  }
  //Serial.print("UV: "+String(quality) + " ");
  //Serial.print(UV_index);
  //Serial.println();

  
  //////////////////////////////////////////////////SENSOR DE LLUVIA
  int value = 0;
  value =  analogRead(A2);;  //lectura digital de pin
  if (value <700)
  {
      //Serial.print("Lluvia: si");
      cont2=1;
  }
  else
  {
      //Serial.print("Lluvia: no");
      cont2=0;
  }
  ////////////////////////////////////////////////////RELAY
  if(temp_event.temperature>=30)
    digitalWrite(relay1, LOW);
  else
    digitalWrite(relay1, HIGH);
  
  if(MQ2.readSensor()>=150)
  {
    digitalWrite(relay2, LOW);
    if(centinela==0)
    {
      Serial1.print(pressure_event.pressure+String('@')+temp_event.temperature+String('@')+UV_index+String('@')+cont2+String('@')+MQ2.readSensor()+String('@')+latitude+String('@')+longitude+String('@')+!digitalRead(relay2)+String('@'));
      Serial.println(pressure_event.pressure+String('@')+temp_event.temperature+String('@')+UV_index+String('@')+cont2+String('@')+MQ2.readSensor()+String('@')+latitude+String('@')+longitude+String('@')+!digitalRead(relay2)+String('@'));
      centinela=1;
    }
  }
  else
  {
    digitalWrite(relay2, HIGH);
    centinela=0;
  }
  ////////////////////////////////////GPS
  
  while(serialgps.available())
  {
    int c=serialgps.read();
    if(gps.encode(c))
    {
      gps.f_get_position(&latitude, &longitude);
      
    }
  }   
  
  ///////////////////////////////////LCD
    lcd.setCursor(0, 0);
    lcd.print(now.year()+String('/')+now.month()+String('/')+now.day()+String(' ')+now.hour()+String(':')+now.minute()+String(':')+ now.second()   ) ;  
    if((cont1==0)||(cont1==5)||(cont1==10)||(cont1==15))
      lcd.clear();
    
    cont1++;
    if(cont1<5)
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(now.year()+String('/')+now.month()+String('/')+now.day()+String(' ')+now.hour()+String(':')+now.minute()+String(':')+ now.second()   ) ;  
      
      lcd.setCursor(0, 1);
      lcd.print(String("Temperatura: ")+temp_event.temperature);
      lcd.setCursor(0, 2);
      lcd.print(String("Presion: ")+pressure_event.pressure);
      lcd.setCursor(0, 3);
      lcd.print(String("Altura: ")+bmp.readAltitude(1013.25));
      //lcd.print(String("Altura: ")+bmp.readAltitude(pressure_event.pressure));
    }
    if((cont1==0)||(cont1==5)||(cont1==10)||(cont1==15))
      lcd.clear();
    if((cont1>=5)&&(cont1<10))
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(now.year()+String('/')+now.month()+String('/')+now.day()+String(' ')+now.hour()+String(':')+now.minute()+String(':')+ now.second()   ) ;  
      
      lcd.setCursor(0, 1);
      lcd.print(String("Temp Int: ")+(int)temperature);
      lcd.setCursor(0, 2);
      lcd.print(String("Humedad: ")+(int)humidity);
      lcd.setCursor(0, 3);
      lcd.print(String("PPM CO: ")+MQ2.readSensor());
      
    }
    if((cont1==0)||(cont1==5)||(cont1==10)||(cont1==15))
      lcd.clear();
    if((cont1>=10)&&(cont1<15))
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(now.year()+String('/')+now.month()+String('/')+now.day()+String(' ')+now.hour()+String(':')+now.minute()+String(':')+ now.second()   ) ;  
      lcd.setCursor(0, 1);
      lcd.print(String("UV: ")+UV_index);
      lcd.setCursor(0, 2);
      lcd.print(String("lluvia: "));
      if(cont2==1)
      lcd.print(String("Si "));
      if(cont2==0)
      lcd.print(String("No ")); 
    }
    if((cont1==0)||(cont1==5)||(cont1==10)||(cont1==15))
      lcd.clear();
    if(cont1>=15)
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(now.year()+String('/')+now.month()+String('/')+now.day()+String(' ')+now.hour()+String(':')+now.minute()+String(':')+ now.second()   ) ;  
      lcd.setCursor(0, 1);
      lcd.print(String("Latitud: "));
      lcd.setCursor(10, 1);
      lcd.print(latitude,5);
      lcd.setCursor(0, 2);
      lcd.print(String("Longitud: "));
      lcd.setCursor(10, 2);
      lcd.print(longitude,5);
    }
    if(cont1>=20)
    {
      cont1=0;
    }
      
    ///////////////////////////////////////////////////////////////DATOS A ESP8266
    
    if((cont3>30)||(cont3==0))
    {
      Serial.print(now.year(), DEC);
      Serial.print('/');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.print(now.day(), DEC);
      Serial.print(' ');
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.println();
      
       Serial1.print(pressure_event.pressure+String('@')+temp_event.temperature+String('@')+UV_index+String('@')+cont2+String('@')+MQ2.readSensor()+String('@'));
       Serial1.print(latitude,5);
       Serial1.print(String('@'));
       Serial1.print(longitude,5);
       Serial1.print(String('@'));
       Serial1.print(!digitalRead(relay1)+String('@'));

       Serial.print(pressure_event.pressure+String('@')+temp_event.temperature+String('@')+UV_index+String('@')+cont2+String('@')+MQ2.readSensor()+String('@'));
       Serial.print(latitude,5);
       Serial.print(String('@'));
       Serial.print(longitude,5);
       Serial.print(String('@'));
       Serial.println(!digitalRead(relay1)+String('@'));
      //Serial.println(pressure_event.pressure+String('@')+temp_event.temperature+String('@')+UV_index+String('@')+cont2+String('@')+MQ2.readSensor()+String('@')+latitude+String('@')+longitude+String('@')+!digitalRead(relay1)+String('@'));
       
    }
    if(cont3>30)
      cont3=0;

    cont3++;
    /////////////////////////////////////////////////////////////////
    //Serial.println();
    //Serial.println();
    delay(1000);
  
}
