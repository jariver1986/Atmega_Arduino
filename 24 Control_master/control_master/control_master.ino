  
int option;
int piston1 = 10;
int piston2 = 11;
int piston3 = 12;
int piston4 = 13;
int piston5 = 6;
int piston6 = 7;
int piston7 = 8;
int piston8 = 9;

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

void loop()
{
  if (Serial.available()>0)
  {
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(piston1, LOW);
    }
    if(option=='2') 
    {
      digitalWrite(piston1, HIGH);
    }
    if(option=='3') 
    {
      digitalWrite(piston2, LOW);
    }
    if(option=='4') 
    {
      digitalWrite(piston2, HIGH);
    }
    if(option=='5') 
    {
      digitalWrite(piston3, LOW);
    }
    if(option=='6') 
    {
      digitalWrite(piston3, HIGH);
    }
    if(option=='7') 
    {
      digitalWrite(piston4, LOW);
    }
    if(option=='8') 
    {
      digitalWrite(piston4, HIGH);
    }
  }
  option=0;
}
