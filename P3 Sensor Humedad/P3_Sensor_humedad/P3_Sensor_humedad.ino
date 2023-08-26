int humedad=0;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  humedad=analogRead(A0);
  Serial.print("Humedad: ");
  Serial.println(humedad);
  delay(1000);
}
