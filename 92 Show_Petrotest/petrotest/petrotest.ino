int b1 = 2;
int b2 = 3;
int b3 = 4;
int b4 = 5;

void setup()
{
  Serial.begin (115200);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(b4,INPUT);
}
void loop()
{
   if(digitalRead(b1)==HIGH)  
   {
      Serial.print("AAAAAAAAAA");
   }
   delay(5);
   
   if(digitalRead(b3)==HIGH)  
   {
      Serial.print("BBBBBBBBBB");
   }
   
   delay(5);
}
