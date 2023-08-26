int sensor =7;
int salida=0;
 
void setup(){
  Serial.begin(9600);
}
void loop()
{
  if (salida==0)
  {sensor++;}  
  if (salida==1)
  {sensor--;}
  Serial.println(sensor);
  delay(1000);
  if (sensor>10)
  {salida=1;}
  if (sensor<5)
  {salida=0;}
}
