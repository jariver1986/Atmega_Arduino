//A=RVV
//B=VRV
//C=VVR

//CONJUGACION ABCACBC

int tiempo=4;//Tiempo de 4 segundos de encendido
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

int cont1=0;
int cont2=12;

void v1()
{         
digitalWrite(verde1,LOW);
delay(tiempo*1000);
digitalWrite(verde1,HIGH);
delay(800);
}
void r1()
{         
digitalWrite(rojo1,LOW);
delay(tiempo*1000);
digitalWrite(rojo1,HIGH);
delay(800);
}
void v2()
{         
digitalWrite(verde2,LOW);
delay(tiempo*1000);
digitalWrite(verde2,HIGH);
delay(800);
}
void r2()
{         
digitalWrite(rojo2,LOW);
delay(tiempo*1000);
digitalWrite(rojo2,HIGH);
delay(800);
}
void setup()
{
  Serial.begin (9600);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(in1,INPUT);
  pinMode(in2,INPUT);
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
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}
void loop()
{
  
   
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(modo==1)
  {
    if(digitalRead(in1)==HIGH)  //BOTON 1
      {            
          cont1=cont1+1;
          if(cont1==1){r1();}
          if(cont1==2){v1();}
          if(cont1==3){v1();}
          if(cont1==4){v1();}
          if(cont1==5){r1();}
          if(cont1==6){v1();}
          if(cont1==7){v1();}
          if(cont1==8){v1();}
          if(cont1==9){r1();}
          if(cont1==10){r1();}
          if(cont1==11){v1();}
          if(cont1==12){v1();}
          if(cont1==13){v1();}
          if(cont1==14){v1();}
          if(cont1==15){r1();}
          if(cont1==16){v1();}
          if(cont1==17){r1();}
          if(cont1==18){v1();}
          if(cont1==19){v1();}
          if(cont1==20){v1();}
          if(cont1==21){r1();}
          
          if(cont1>=21)
          {
            cont1=0;
          }
          
       } 
      if(digitalRead(in2)==HIGH)  //BOTON2
      {
          cont2=cont2+1;
          if(cont2==1){r2();}
          if(cont2==2){v2();}
          if(cont2==3){v2();}
          if(cont2==4){v2();}
          if(cont2==5){r2();}
          if(cont2==6){v2();}
          if(cont2==7){v2();}
          if(cont2==8){v2();}
          if(cont2==9){r2();}
          if(cont2==10){r2();}
          if(cont2==11){v2();}
          if(cont2==12){v2();}
          if(cont2==13){v2();}
          if(cont2==14){v2();}
          if(cont2==15){r2();}
          if(cont2==16){v2();}
          if(cont2==17){r2();}
          if(cont2==18){v2();}
          if(cont2==19){v2();}
          if(cont2==20){v2();}
          if(cont2==21){r2();}
          
          if(cont2>=21)
          {
            cont2=0;
          }
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
