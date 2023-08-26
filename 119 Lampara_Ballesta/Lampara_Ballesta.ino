int centinela =0;
void setup() 
{
  // put your setup code here, to run once:
pinMode(2, INPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
Serial.begin(9600);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
digitalWrite(10,LOW);

digitalWrite(8, HIGH);
delay(500);
digitalWrite(8, LOW);
delay(200);

digitalWrite(9, HIGH);
delay(500);
digitalWrite(9, LOW);
delay(200);

digitalWrite(10, HIGH);
delay(100);
digitalWrite(10, LOW);
delay(100);

digitalWrite(8, HIGH);

}

void loop() 
{
  // put your main code here, to run repeatedly:

int estado=digitalRead(2);

  if (analogRead(A0)<400)//if(estado==LOW)
  {
    Serial.print("Alerta ADC = ");    
    centinela=1;
  }
if(centinela==1)
  {
    digitalWrite(10,HIGH);//BUZZER
    delay(100);
    digitalWrite(10,LOW);
    delay(100);
    
    digitalWrite(8,LOW); //LED VERDE
    digitalWrite(9,HIGH);//LED ROJO
    delay(200);
    digitalWrite(9,LOW);
    delay(1000);
  }

 
Serial.println(analogRead(A0));  

delay(200);

}
