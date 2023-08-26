int sensor =0;
int salida=0;
 
void setup(){
  Serial.begin(9600);
}
void loop()
{
  sensor = analogRead(A0);
  //salida = map(sensor, 0, 1023, 0, 255);  
  Serial.println("A"+String(sensor)+"B");
  //delay(1);
}
