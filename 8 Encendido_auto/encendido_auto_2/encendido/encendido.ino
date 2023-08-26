int star=13;
int accesorio=12;
int engine=8;
byte modo=0;

int estado=0;

void setup()
{
  Serial.begin(9600);
  digitalWrite(accesorio,LOW);
  digitalWrite(engine,LOW);
  digitalWrite(star,LOW);
}

void loop()
{
 if(Serial.available()>0)
 {
     estado = Serial.read();
      if (estado =='1')
       {
         modo = not(modo);
       }
       
        if (modo=255)
        {
           digitalWrite(accesorio,HIGH);
           delay(100);
           digitalWrite(engine,HIGH);
           delay(300);
           digitalWrite(star,HIGH);
           delay(200);
           digitalWrite(star,LOW);
      }  
       if (modo=0)
      {
           digitalWrite(engine,LOW);
           delay(100);
           digitalWrite(accesorio,LOW);
      }  
           
     estado=0;      
           
           
   }
}  
