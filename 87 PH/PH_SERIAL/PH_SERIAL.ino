#include "DHT.h"
#define SensorPin 0            //pH meter Analog output to Arduino Analog Input 0 => A0 con Po
#define Offset -3.50            //deviation compensate
unsigned long int avgValue;     //Store the average value of the sensor feedback
#define DHTPIN 4       //Pin de conexión dht con A0
#define DHTTYPE DHT11   //Modelo
DHT dht(DHTPIN, DHTTYPE);
float temperatura=0;
int contador=0;
int dato3=1;
int UVOUT = A5; //Output from the sensor
int REF_3V3 = A4; //3.3V power on the Arduino board


void setup()
{ 
  dht.begin();
  Serial.begin(115200);  
  //Serial.println("Sensor PH");    //Test the serial monitor
  pinMode(UVOUT, INPUT);
 pinMode(REF_3V3, INPUT);
}
void loop()
{
  int buf[10];                //buffer for read analog
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=14-(3.5*phValue+Offset);                      //convert the millivolt into pH value
  delay(10);
  
  //Serial.print("PH: ");  
  //Serial.println(phValue,2);

  temperatura=dht.readTemperature();
  //Serial.print("T:");  
  //Serial.println(temperatura,2);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  int uvLevel = averageAnalogRead(UVOUT);
 int refLevel = averageAnalogRead(REF_3V3);
 //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
 float outputVoltage = 3.3 / refLevel * uvLevel;  
 float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);


 
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  contador=contador+1;
  if(contador>150)
  {
    Serial.print(String(temperatura,2)+"T"+String(phValue,2)+"P"+String(uvIntensity,2)+"V");
    Serial.print(String(temperatura,2)+"T"+String(phValue,2)+"P"+String(uvIntensity,2)+"V");
    contador=0;
  }
  
  delay(100);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
}
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return(runningValue);  
}
//The Arduino Map function but for floats
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


  
