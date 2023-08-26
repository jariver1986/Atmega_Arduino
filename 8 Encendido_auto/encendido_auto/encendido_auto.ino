int option='1';
int accesorio = 13;
int engine = 12;
int star = 8;
int centinela=0;

 
void setup()
{
  Serial.begin(9600);
  pinMode(star,OUTPUT);
  pinMode(engine,OUTPUT);
  pinMode(accesorio,OUTPUT);
}
//CLAVE 20151607    AÑO DIA MES

void loop()
{
  
  if (Serial.available()>0)
  {
    option=Serial.read(); 
    if(option=='1') 
    {
      centinela = !centinela;
    }
    
    if (centinela==1)
    {
      digitalWrite(accesorio, HIGH);              
      Serial.print('ACCESORIO \n');
      delay(1000);
      digitalWrite(engine, HIGH);              
      Serial.print('ENGINE \n');
      delay(1000);
      digitalWrite(star, HIGH);              
      Serial.print('ESTAR ON \n');
      delay(200);
      digitalWrite(star, LOW);              
      Serial.print('ESTAR OFF \n');
    }
    if (centinela==0)
    {
      digitalWrite(engine, LOW);              
      delay(200);
      digitalWrite(accesorio,LOW);              
      delay(200);
      Serial.print('SISTEMA APAGADO\n');    
    }
  }

  }

