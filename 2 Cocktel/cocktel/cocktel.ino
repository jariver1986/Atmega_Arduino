	
int option;
int piston1 = 13;
int piston2 = 12;
int piston3 = 8;
int piston4 = 7;
int piston5 = 4;
int piston6 = 2;
int piston7 = 3;
int piston8 = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(piston1, OUTPUT); 
  pinMode(piston2, OUTPUT); 
  pinMode(piston3, OUTPUT); 
  pinMode(piston4, OUTPUT); 
  pinMode(piston5, OUTPUT); 
  pinMode(piston6, OUTPUT); 
  pinMode(piston7, OUTPUT); 
  pinMode(piston8, OUTPUT); 
  digitalWrite(piston1, HIGH);
  digitalWrite(piston2, HIGH);
  digitalWrite(piston3, HIGH);
  digitalWrite(piston4, HIGH);
  digitalWrite(piston5, HIGH);
  digitalWrite(piston6, HIGH);
  digitalWrite(piston7, HIGH);
  digitalWrite(piston8, HIGH);
}
void dosis(int d1,int d2,int d3,int d4,int d5,int d6, int d7,int d8)
{
  
      digitalWrite(piston1, LOW); delay(d1); digitalWrite(piston1, HIGH);
      delay(50);
      digitalWrite(piston2, LOW); delay(d2); digitalWrite(piston2, HIGH);
      delay(50);
      digitalWrite(piston3, LOW); delay(d3); digitalWrite(piston3, HIGH);
      delay(50);
      digitalWrite(piston4, LOW); delay(d4); digitalWrite(piston4, HIGH);
      delay(50);
      digitalWrite(piston5, LOW); delay(d5); digitalWrite(piston5, HIGH);
      delay(50);
      digitalWrite(piston6, LOW); delay(d6); digitalWrite(piston6, HIGH);
      delay(50);
      digitalWrite(piston7, LOW); delay(d7); digitalWrite(piston7, HIGH);
      delay(50);
      digitalWrite(piston8, LOW); delay(d8); digitalWrite(piston8, HIGH);
      Serial.println("R");
}
void loop(){
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='a') 
    {
      dosis(0,0,5500,0,0,3500,1000,0);
    }
    if(option=='b') 
    {
     dosis(0,0,7500,0,12500,0,500,0);
    }
    if(option=='c') 
    {
       dosis(0,0,0,0,30000,0,500,0);
    }
    if(option=='d') 
    {
       dosis(0,0,7500,0,12500,0,0,0);
    }
    if(option=='e') 
    {
       dosis(0,0,0,0,12500,0,0,25000);
    }
    if(option=='f') 
    {
       dosis(9000,0,0,3000,0,0,500,0);
    }
    if(option=='g') 
    {
       dosis(0,7500,0,3000,0,0,500,0);
    }
    if(option=='h') 
    {
       dosis(4500,0,4500,0,0,3500,1000,0);
    }
    if(option=='i') 
    {
       dosis(4500,0,0,3000,0,3500,1000,0);
    }
    if(option=='j') 
    {
       dosis(0,0,0,5000,0,0,2000,0);
    }
    if(option=='k') 
    {
       dosis(0,0,0,3500,0,3500,500,12500);
    }
    if(option=='l') 
    {
       dosis(0,0,11000,0,0,0,0,0);
    }
    if(option=='m') 
    {
       dosis(0,11000,0,0,0,0,0,0);
    }
    if(option=='n') 
    {
       dosis(9000,0,0,0,0,0,0,0);
    }
  }
  option=0;
}
