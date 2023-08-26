#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define SensorPin 0            //pH meter Analog output to Arduino Analog Input 0
#define Offset -3.50            //deviation compensate
unsigned long int avgValue;     //Store the average value of the sensor feedback
const int rele1 = 8;
const int rele2 = 9;
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////MODIFICACION DE TIEMPOS///////////////////////////////////////////////////
const int tiempo_espera = 2000; //aqui modifique los valores
const int tiempo_activacion_bomba = 500; //aqui modifique los valores
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void setup()
{ 
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  lcd.begin(16, 2);
  lcd.print("Sensor PH");
  lcd.setCursor(0,2);
  lcd.print("PH: ");
  pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Sensor PH");    //Test the serial monitor
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
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  lcd.setCursor(4,2);
  lcd.print(phValue);
  Serial.println(" ");

  if(phValue < 7) {
    
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, HIGH);
  delay(tiempo_activacion_bomba);  //tiempo de encendido de bomba 1
  digitalWrite(rele1, HIGH);
  delay(tiempo_espera); //tiempo de espera para volver a hacer lectura del sensor
  }else if(phValue > 7) {
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, LOW);  
  delay(tiempo_activacion_bomba); //tiempo de encendido de bomba 2
  digitalWrite(rele2, HIGH);
  delay(tiempo_espera); //tiempo de espera para volver a hacer lectura del sensor
  }
  
}
