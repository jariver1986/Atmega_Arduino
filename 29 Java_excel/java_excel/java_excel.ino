
int option;

void setup() // Se ejecuta cada vez que el Arduino se inicia
{
 Serial.begin(9600);
}
 
void loop() // Esta funcion se mantiene ejecutando
{           //  cuando este energizado el Arduino
   if (Serial.available()>0)
  {
    option=Serial.read();
    
  }
  if(option=='1') 
    {
      Serial.println("18");
      Serial.println("02");
      Serial.println("17");
      option=0;
    }
    //delay(2000);
}
 

