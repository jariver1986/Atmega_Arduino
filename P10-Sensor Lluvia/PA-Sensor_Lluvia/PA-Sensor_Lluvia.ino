void setup() 
{
  Serial.begin(9600);
  pinMode(2,INPUT);
}

void loop() 
{
  int estado=digitalRead(2);
  if(estado==HIGH)
  {
    Serial.print("Lluvia: ");
    //Serial.println(analogRead(A0));  
  }
  Serial.println(analogRead(A0));  
  delay(2000);
}
