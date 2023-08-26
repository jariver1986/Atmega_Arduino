
int option;
int a=13;
int b=12;
int c=11;
int d=10;
int e=9;
int f=8;

void setup()
{
  Serial.begin(9600);
  pinMode(a, OUTPUT); 
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);

}
 
void loop()
{
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {digitalWrite(8, HIGH);}
    if(option=='2') 
    {digitalWrite(8, LOW);}

    if(option=='3') 
    {digitalWrite(9, HIGH);}
    if(option=='4') 
    {digitalWrite(9, LOW);}

      if(option=='5') 
    {digitalWrite(10, HIGH);}
    if(option=='6') 
    {digitalWrite(10, LOW);}

   if(option=='7') 
    {digitalWrite(11, HIGH);}
    if(option=='8') 
    {digitalWrite(11, LOW);}

   if(option=='9') 
    {digitalWrite(12, HIGH);}
    if(option=='A') 
    {digitalWrite(12, LOW);}

   if(option=='B') 
    {digitalWrite(13, HIGH);}
    if(option=='C') 
    {digitalWrite(13, LOW);}

  }   
  
}
