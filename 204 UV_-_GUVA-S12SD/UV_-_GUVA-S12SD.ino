#include <SPI.h>
#include <Wire.h>

void uv_index()
{

  float sensorVoltage;   
  float sensorValue;
  int UV_index;
  String quality =""; 
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
  Serial.print("UV: "+String(quality) + " ");
  Serial.print(UV_index);

  Serial.println();
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
   uv_index();

}
