float sensor =0;
float sensor2 =0;
int salida=0;
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  digitalWrite(13,LOW);
}
void loop()
{
  //Serial.println(sensor);
  sensor =(analogRead(A0)*48875)/100000;
  sensor2 = sensor+32;
  //salida = map(sensor, 0, 1023, 0, 255);
  Serial.println("Temperatura:_"+String(sensor)+"_°C ");
  Serial.println("Temperatura:_"+String(sensor)+"_°F ");
  if((sensor>0)&&(sensor<=10))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);
  }  



  
  delay(1000);
}
