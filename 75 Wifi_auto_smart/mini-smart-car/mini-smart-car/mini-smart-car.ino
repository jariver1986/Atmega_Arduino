int option=0;
int valvula1=1;
int valvula2=2;

 
void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
   Serial.println("Hola car...");
  pinMode(valvula1,OUTPUT); 
  pinMode(valvula2,OUTPUT); 
 

}

 
void loop() 
{

  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(valvula1, LOW);
      delay(1000);
      digitalWrite(valvula1, HIGH);
      delay(500);
      Serial.println("ok1");
      option=0;
    }
    if(option=='2') 
    {
      digitalWrite(valvula2, LOW);
      Serial.println("ok2");
      
      delay(1000);
      digitalWrite(valvula2, HIGH);
      delay(500);
      option=0;
    }
  }  
   
}

