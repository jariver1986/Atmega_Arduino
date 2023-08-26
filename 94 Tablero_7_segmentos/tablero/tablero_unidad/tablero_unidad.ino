int a1 = 29;
int b1 = 30;
int c1 = 31;
int d1 = 32;
int e1 = 33;
int f1 = 34;
int g1 = 35;

int contador=0;
int contador2=0;
int contador3=0;

int dato=0;
void setup()
{
  Serial.begin (9600);
  pinMode(a1,OUTPUT);
  pinMode(b1,OUTPUT);
  pinMode(c1,OUTPUT);
  pinMode(d1,OUTPUT);
  pinMode(e1,OUTPUT);
  pinMode(f1,OUTPUT);
  pinMode(g1,OUTPUT);
    digitalWrite(a1, LOW); 
    digitalWrite(b1, LOW); 
    digitalWrite(c1, LOW); 
    digitalWrite(d1, LOW); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, LOW); 
    digitalWrite(g1, LOW); 
  
}
void apagar()
{
  digitalWrite(a1, LOW); 
    digitalWrite(b1, LOW); 
    digitalWrite(c1, LOW); 
    digitalWrite(d1, LOW); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, LOW); 
    digitalWrite(g1, LOW); 
  }
void uno()
{
    digitalWrite(a1, LOW); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, LOW); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, LOW); 
    digitalWrite(g1, LOW); 
}

void dos()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, LOW); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, HIGH); 
    digitalWrite(f1, LOW); 
    digitalWrite(g1, HIGH); 
}


void tres()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, LOW); 
    digitalWrite(g1, HIGH); 
}

void cuatro()
{
    digitalWrite(a1, LOW); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, LOW); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, HIGH); 
    digitalWrite(g1, HIGH); 
}

void cinco()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, LOW); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, HIGH); 
    digitalWrite(g1, HIGH); 
}

void seis()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, LOW); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, HIGH); 
    digitalWrite(f1, HIGH); 
    digitalWrite(g1, HIGH); 
}

void siete()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, LOW); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, LOW); 
    digitalWrite(g1, LOW); 
}

void ocho()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, HIGH); 
    digitalWrite(f1, HIGH); 
    digitalWrite(g1, HIGH); 
}


void nueve()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, LOW); 
    digitalWrite(f1, HIGH); 
    digitalWrite(g1, HIGH); 
}

void cero()
{
    digitalWrite(a1, HIGH); 
    digitalWrite(b1, HIGH); 
    digitalWrite(c1, HIGH); 
    digitalWrite(d1, HIGH); 
    digitalWrite(e1, HIGH); 
    digitalWrite(f1, HIGH); 
    digitalWrite(g1, LOW); 
}

void loop()
{
  if (Serial.available()>0)
  {
    apagar();
    delay(500);
    dato=Serial.read();
    if(dato=='1')
    {uno(); }
    if(dato=='2')
    {dos();  }
    if(dato=='9')
    {nueve();  }
   delay(2000);
  }

  contador= contador+1;
  if(contador==9)
  {
    nueve();
    
    contador=0;
    contador2= contador2+1;  
    if(contador2==9)
    {
      nueve();
      contador2=0;
      contador3= contador3+1;  
    }
    delay(1000);
  }
  if(contador==0) { cero();   }
  if(contador==1) { uno();    }
  if(contador==2) { dos();    }
  if(contador==3) { tres();   }
  if(contador==4) { cuatro(); }
  if(contador==5) { cinco();  }
  if(contador==6) { seis();   }
  if(contador==7) { siete();  }
  if(contador==8) { ocho();   }
  

  
  delay(1000);
  
   
}
