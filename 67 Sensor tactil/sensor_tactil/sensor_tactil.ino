const int sensorPin = 9;
const int sensorPin10 = 10;
int variable=0;
 
void setup()
{
   Serial.begin(9600);
   pinMode(sensorPin, INPUT);
   pinMode(sensorPin10, INPUT);
}
 
void loop()
{
   int estado = digitalRead(sensorPin);
   int estado10 = digitalRead(sensorPin10);
   if (estado10 == HIGH)
   {
      variable=variable+1;
      Serial.println(variable);   
   }
   
   if (variable>=3)
   {
      variable=0;
   }
   
   delay(200);
   
}
