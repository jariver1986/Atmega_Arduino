int option=0;
 
void setup(void) 
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}
 
void loop(void) 
{

  if (Serial.available()>0)
    {
      //leemos la opcion enviada
      option=Serial.read();
      if(option=='1') 
      {
        digitalWrite(2, HIGH);
        Serial.println("Encendido");
        option=0;
        
      }
      if(option=='2') 
      {
        digitalWrite(2, LOW);
        Serial.println("apagado");
        option=0;
      }
      
    }
}



