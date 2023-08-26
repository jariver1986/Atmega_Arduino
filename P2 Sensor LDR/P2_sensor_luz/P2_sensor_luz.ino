int dato=0;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
dato=analogRead(A2);
Serial.println(dato);
delay(1000);
}
