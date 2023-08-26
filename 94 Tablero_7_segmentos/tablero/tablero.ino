int a1 = 2;
int b1 = 3;
int c1 = 4;
int d1 = 5;
int e1 = 6;
int f1 = 7;
int g1 = 8;
int a2 = 22;
int b2 = 23;
int c2 = 24;
int d2 = 25;
int e2 = 26;
int f2 = 27;
int g2 = 28;
int a3 = 29;
int b3 = 30;
int c3 = 31;
int d3 = 32;
int e3 = 33;
int f3 = 34;
int g3 = 35;

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

  pinMode(a2,OUTPUT);
  pinMode(b2,OUTPUT);
  pinMode(c2,OUTPUT);
  pinMode(d2,OUTPUT);
  pinMode(e2,OUTPUT);
  pinMode(f2,OUTPUT);
  pinMode(g2,OUTPUT);

  pinMode(a3,OUTPUT);
  pinMode(b3,OUTPUT);
  pinMode(c3,OUTPUT);
  pinMode(d3,OUTPUT);
  pinMode(e3,OUTPUT);
  pinMode(f3,OUTPUT);
  pinMode(g3,OUTPUT);
  
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
    digitalWrite(a2, LOW); 
    digitalWrite(b2, LOW); 
    digitalWrite(c2, LOW); 
    digitalWrite(d2, LOW); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, LOW); 
    digitalWrite(g2, LOW);
    digitalWrite(a3, LOW); 
    digitalWrite(b3, LOW); 
    digitalWrite(c3, LOW); 
    digitalWrite(d3, LOW); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, LOW); 
    digitalWrite(g3, LOW);
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
void uno1()
{
    digitalWrite(a2, LOW); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, LOW); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, LOW); 
    digitalWrite(g2, LOW); 
}
void uno11()
{
    digitalWrite(a3, LOW); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, LOW); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, LOW); 
    digitalWrite(g3, LOW); 
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
void dos2()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, LOW); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, HIGH); 
    digitalWrite(f2, LOW); 
    digitalWrite(g2, HIGH); 
}
void dos22()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, LOW); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, HIGH); 
    digitalWrite(f3, LOW); 
    digitalWrite(g3, HIGH); 
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
void tres3()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, LOW); 
    digitalWrite(g2, HIGH); 
}
void tres33()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, LOW); 
    digitalWrite(g3, HIGH); 
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
void cuatro4()
{
    digitalWrite(a2, LOW); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, LOW); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, HIGH); 
    digitalWrite(g2, HIGH); 
}
void cuatro44()
{
    digitalWrite(a3, LOW); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, LOW); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, HIGH); 
    digitalWrite(g3, HIGH); 
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
void cinco5()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, LOW); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, HIGH); 
    digitalWrite(g2, HIGH); 
}
void cinco55()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, LOW); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, HIGH); 
    digitalWrite(g3, HIGH); 
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
void seis6()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, LOW); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, HIGH); 
    digitalWrite(f2, HIGH); 
    digitalWrite(g2, HIGH); 
}
void seis66()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, LOW); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, HIGH); 
    digitalWrite(f3, HIGH); 
    digitalWrite(g3, HIGH); 
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
void siete7()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, LOW); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, LOW); 
    digitalWrite(g2, LOW); 
}
void siete77()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, LOW); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, LOW); 
    digitalWrite(g3, LOW); 
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
void ocho8()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, HIGH); 
    digitalWrite(f2, HIGH); 
    digitalWrite(g2, HIGH); 
}

void ocho88()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, HIGH); 
    digitalWrite(f3, HIGH); 
    digitalWrite(g3, HIGH); 
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
void nueve9()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, LOW); 
    digitalWrite(f2, HIGH); 
    digitalWrite(g2, HIGH); 
}
void nueve99()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, LOW); 
    digitalWrite(f3, HIGH); 
    digitalWrite(g3, HIGH); 
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
void cero0()
{
    digitalWrite(a2, HIGH); 
    digitalWrite(b2, HIGH); 
    digitalWrite(c2, HIGH); 
    digitalWrite(d2, HIGH); 
    digitalWrite(e2, HIGH); 
    digitalWrite(f2, HIGH); 
    digitalWrite(g2, LOW); 
}
void cero00()
{
    digitalWrite(a3, HIGH); 
    digitalWrite(b3, HIGH); 
    digitalWrite(c3, HIGH); 
    digitalWrite(d3, HIGH); 
    digitalWrite(e3, HIGH); 
    digitalWrite(f3, HIGH); 
    digitalWrite(g3, LOW); 
}
void loop()
{
  if (Serial.available()>0)
  {
    dato=Serial.read();
    if(dato=='1')
    {uno(); }
    if(dato=='2')
    {dos();  }
  }

  contador= contador+1;
  if(contador==9)
  {
    nueve();
    contador=0;
    contador2= contador2+1;  
    if(contador2==9)
    {
      nueve9();
      //contador2=0;
      contador3= contador3+1;  
      if(contador3==9)
      {
        nueve99();
        contador3= 0;  
      }
    }
    delay(400);
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
  if(contador==9) { nueve();  }

  if(contador2==0) { cero0();   }
  if(contador2==1) { uno1();    }
  if(contador2==2) { dos2();    }
  if(contador2==3) { tres3();   }
  if(contador2==4) { cuatro4(); }
  if(contador2==5) { cinco5();  }
  if(contador2==6) { seis6();   }
  if(contador2==7) { siete7();  }
  if(contador2==8) { ocho8();   }
  if(contador2==9) { nueve9();  }

  if(contador3==0) { cero00();   }
  if(contador3==1) { uno11();    }
  if(contador3==2) { dos22();    }
  if(contador3==3) { tres33();   }
  if(contador3==4) { cuatro44(); }
  if(contador3==5) { cinco55();  }
  if(contador3==6) { seis66();   }
  if(contador3==7) { siete77();  }
  if(contador3==8) { ocho88();   }
  if(contador3==9) { nueve99();  }
  
  delay(500);
  
   
}
