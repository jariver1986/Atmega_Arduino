int b1 = 2;
int b2 = 3;
int b3 = 4;
int modo=1;

int verde1 = 5;
int rojo1  = 6;
int verde2 = 7;
int rojo2  = 8;

int in1=9;
int in2=10;

int prueba = 13;

int aleatorio=0;
int dato=0;
void setup()
{
  Serial.begin (9600);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(verde1,OUTPUT);
  pinMode(rojo1,OUTPUT);
  pinMode(verde2,OUTPUT);
  pinMode(rojo2,OUTPUT);
  pinMode(prueba,OUTPUT);
  randomSeed(1);
  digitalWrite(verde1,HIGH);
  digitalWrite(rojo1,HIGH);
  digitalWrite(verde2,HIGH);
  digitalWrite(rojo2,HIGH);
}
void loop()
{
  if (Serial.available()>0)
  {
    dato=Serial.read();
    if(dato=='1')
    {digitalWrite(verde1,HIGH); }
    if(dato=='2')
    {digitalWrite(verde1,LOW);  }
    if(dato=='3')
    {digitalWrite(rojo1,HIGH);  }
    if(dato=='4')
    {digitalWrite(rojo1,LOW);   }
    if(dato=='5')
    {digitalWrite(verde2,HIGH); }
    if(dato=='6')
    {digitalWrite(verde2,LOW);  }
    if(dato=='7')
    {digitalWrite(rojo2,HIGH);  }
    if(dato=='8')
    {digitalWrite(rojo2,LOW);   }
    if(dato=='9')
    {digitalWrite(prueba,HIGH);  }
    if(dato=='a')
    {digitalWrite(prueba,LOW);   }
  }
  
   if(digitalRead(b1)==HIGH)  
   {
    modo=1;
        Serial.println("MODO 1");
        delay(200);
   }
   if(digitalRead(b2)==HIGH)  
   {
    modo=2;
    Serial.println("MODO 2");
    delay(200);
   }
   if(digitalRead(b3)==HIGH)  
   {
    modo=3;
    Serial.println("MODO 3");
    delay(200);
   }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(modo==1)
  {
    if(digitalRead(in1)==HIGH)  
      {
        aleatorio=random(1,4);
        if((aleatorio==1)||(aleatorio==2))
        {
          digitalWrite(verde1,LOW);
          delay(8000);
          digitalWrite(verde1,HIGH);
          delay(800);
        }
        if((aleatorio==3)||(aleatorio==4))
        {
          digitalWrite(rojo1,LOW);
          delay(8000);
          digitalWrite(rojo1,HIGH);
          delay(800);
        }
        Serial.print("Modo1 IN1: ");
        Serial.println(aleatorio);
       } 
      if(digitalRead(in2)==HIGH)  
      {
        aleatorio=random(1,4);
        if((aleatorio==1)||(aleatorio==2))
        {
          digitalWrite(verde2,LOW);
          delay(8000);
          digitalWrite(verde2,HIGH);
          delay(800);
        }
        if((aleatorio==3)||(aleatorio==4))
        {
          digitalWrite(rojo2,LOW);
          delay(8000);
          digitalWrite(rojo2,HIGH);
          delay(800);
        }
        Serial.print("Modo1 IN2: ");
        Serial.println(aleatorio);
       } 
   }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(modo==2)
  {
    if(digitalRead(in1)==HIGH)  
      {
        aleatorio=random(1,4);
        if(aleatorio==1)
        {
          digitalWrite(verde1,LOW);
          delay(8000);
          digitalWrite(verde1,HIGH);
          delay(800);
        }
        if((aleatorio==2)||(aleatorio==3)||(aleatorio==4))
        {
          digitalWrite(rojo1,LOW);
          delay(8000);
          digitalWrite(rojo1,HIGH);
          delay(800);
        }
        Serial.print("Modo2 IN1: ");
        Serial.println(aleatorio);
       } 
      if(digitalRead(in2)==HIGH)  
      {
        aleatorio=random(1,4);
        if(aleatorio==1)
        {
          digitalWrite(verde2,LOW);
          delay(8000);
          digitalWrite(verde2,HIGH);
          delay(800);
        }
        if((aleatorio==2)||(aleatorio==3)||(aleatorio==4))
        {
          digitalWrite(rojo2,LOW);
          delay(8000);
          digitalWrite(rojo2,HIGH);
          delay(800);
        }
        Serial.print("Modo2 IN2: ");
        Serial.println(aleatorio);
       } 
   }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(modo==3)
  {
    if(digitalRead(in1)==HIGH)  
      {
        aleatorio=random(1,4);
        if((aleatorio==2)||(aleatorio==3)||(aleatorio==1)||(aleatorio==4))
        {
          digitalWrite(rojo1,LOW);
          delay(8000);
          digitalWrite(rojo1,HIGH);
          delay(800);
        }
        Serial.print("Modo3 IN1: ");
        Serial.println(aleatorio);
       } 
      if(digitalRead(in2)==HIGH)  
      {
        aleatorio=random(1,4);
        if((aleatorio==2)||(aleatorio==3)||(aleatorio==1)||(aleatorio==4))
        {
          digitalWrite(rojo2,LOW);
          delay(8000);
          digitalWrite(rojo2,HIGH);
          delay(800);
        }
        Serial.print("Modo3 IN2: ");
        Serial.println(aleatorio);
       } 
   }
}
