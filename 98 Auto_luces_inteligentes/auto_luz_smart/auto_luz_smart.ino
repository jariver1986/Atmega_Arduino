int luz=0;
int lluvia=0;

int centinela=0;
void setup() 
{
  pinMode(2,INPUT);//Auto ON
  pinMode(3,INPUT);//sensor de lluvia
  pinMode(8,OUTPUT);//Salida relay
  pinMode(9,OUTPUT);//Salida relay
  pinMode(10,OUTPUT);//Salida relay
  pinMode(13,OUTPUT);//Salida relay
  Serial.begin(9600);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  
}

void loop() 
{
  if (digitalRead(2) == HIGH) //Auto ON
  {
    ////////////////////////////////////////////////////////
    lluvia=analogRead(A1);
    //Serial.println(lluvia);
    if(lluvia<1000)
    {
      digitalWrite(8, LOW); //Salida relay
      //Serial.println("encendido");
      digitalWrite(13, HIGH);
    }
    else
    {
      digitalWrite(8, HIGH); //Salida relay
      //Serial.println("apagado");
      digitalWrite(13, LOW); 
    }
    delay(500);
    ////////////////////////////////////////////////////////
    luz=analogRead(A0);
    Serial.println(luz);
    
    if(luz>500)
    {
      digitalWrite(9, LOW); //Salida relay
      
    }
    else
    {
      digitalWrite(9, HIGH); //Salida relay
      
    }
    delay(500);
  /////////////////////////////////////////////////////////////
  centinela=1;
  }
  if ((digitalRead(2) == LOW)&&(centinela==1)) //Auto OFF
  {
    digitalWrite(8, LOW); //Salida relay
    delay(10000);
    digitalWrite(8, HIGH); //Salida relay
    centinela=0;
   }
}
