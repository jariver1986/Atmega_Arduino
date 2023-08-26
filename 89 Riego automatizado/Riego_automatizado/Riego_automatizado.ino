/*Conexiones
 * LCD 2,3,4,5,6,7(RS,RE,D4,D5,D6,D7) ok
 * Teclado 46,47,48,49,50,51,52,53
 * nivel agua 25
 * bomba agua 1 26
 * bomba agua 2 27
 * ventilador 1 28
 * ventilador 2 29
 * RGB1 30,31,32
 * RGB1 33,34,35
 * SONIDO 36
 * DHT11 22
 * DHT11 TIERRA1 23
 * DHT11 TIERRA2 24
 * Humed tierra1 A0
 * Humedad tierra2 A1
 * Luz 1 A2
 * Luz 2 A3
 * PWM1 A4 POT
 * PWM2 A5 POT 
 * TP1 A6
 * TP2 7
 * HP1 9 PWM
 * HP2 10 PWM
 */
#include <LiquidCrystal.h>      
#include <Keypad.h>
#include <SimpleDHT.h>
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);//(RS,RE,D4,D5,D6,D7)
LiquidCrystal lcd(38, 40, 42, 44, 46, 48);//(RS,RE,D4,D5,D6,D7)
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
{
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {5,4,3,2}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
SimpleDHT11 ambiente;
SimpleDHT11 tierra1;
SimpleDHT11 tierra2;

//Variables
int indio=0;
int humedad1=0;
int humedad2=0;
int luz1=0;
int luz2=0;
byte T=0;
byte H=0;
byte T1=0;
byte H1=0;
byte T2=0;
byte H2=0;
int nivel=25;
int riego1=3;
int riego2=3;
int valvula1=26;//Riego1
int valvula2=27;//Riego2
int ventilador1=28;
int ventilador2=29;
int R1=30;
int G1=31;
int BB1=32;
int R2=33;
int G2=34;
int B2=35;
int sonido=36;
int RGB1=0;
int RGB2=0;
int PWM1=255;
int PWM2=255;
int TP1=30;
int TP2=30;
int HP1=50;
int HP2=50;
int contador1=0;
int BUTP1=50;
int BUTP2=50;
int BUHP1=100;
int BUHP2=100;
void setup() 
{
  Serial.begin(9600);
  lcd.begin(20,4); 
  pinMode(nivel,INPUT);//NIVEL AGUA
  pinMode(valvula1,OUTPUT); 
  pinMode(valvula2,OUTPUT); 
  pinMode(ventilador1,OUTPUT); 
  pinMode(ventilador2,OUTPUT); 
  pinMode(R1,OUTPUT); 
  pinMode(G1,OUTPUT); 
  pinMode(BB1,OUTPUT); 
  pinMode(R2,OUTPUT); 
  pinMode(G2,OUTPUT); 
  pinMode(B2,OUTPUT); 
  pinMode(sonido,OUTPUT); 
  pinMode(10,OUTPUT); 
  digitalWrite(valvula1, HIGH);  
  digitalWrite(valvula2, HIGH);  
  digitalWrite(ventilador1, HIGH);  
  digitalWrite(ventilador2, HIGH);  
  digitalWrite(R1, HIGH);  
  digitalWrite(G1, HIGH);  
  digitalWrite(BB1, HIGH);  
  digitalWrite(R2, HIGH);  
  digitalWrite(G2, HIGH);  
  digitalWrite(B2, HIGH);  
  digitalWrite(sonido, LOW);  
  //lcd.clear();
  digitalWrite(sonido, HIGH);
      delay(200);  
      digitalWrite(sonido, LOW);  
      delay(200);  
  lcd.setCursor(0,0); lcd.print("[1]Monitor");//Columna,Fila 
    lcd.setCursor(0,1); lcd.print("[2]Informacion");//Columna,Fila
    lcd.setCursor(0,2); lcd.print("[3]Manual");//Columna,Fila
    lcd.setCursor(0,3); lcd.print("[4]Automatico");//Columna,Fila  
    delay(200);
    digitalWrite(R1, HIGH);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);
    digitalWrite(R2, HIGH);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);    
    analogWrite(10,255);
}

void loop() 
{
  char key = keypad.getKey();
  if(key) {switch (key){case '1': indio=1;lcd.clear();}}//Cuando key "1" es oprimida...
  if(key) {switch (key){case '2': indio=2;lcd.clear();}}//Cuando key "2" es oprimida...
  if(key) {switch (key){case '3': indio=3;lcd.clear();}}//Cuando key "3" es oprimida...
  if(key) {switch (key){case '4': indio=4;lcd.clear();}}//Cuando key "4" es oprimida...
  if(key) {switch (key){case '5': indio=5;lcd.clear();}}//Cuando key "4" es oprimida...
  
  if(key) {switch (key)
  {case 'C': 
    digitalWrite(R1, LOW);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);
    digitalWrite(R2, LOW);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);
  }}//Cuando key "5" es oprimida...
  if(key) {switch (key)
  {case 'D': 
    digitalWrite(R1, HIGH);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);
    digitalWrite(R2, HIGH);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);
  }}//Cuando key "5" es oprimida...
   
  delay(50);
  if(indio==0)
  {
    lcd.setCursor(0,0); lcd.print("[1]Monitor");//Columna,Fila 
    lcd.setCursor(0,1); lcd.print("[2]Informacion");//Columna,Fila
    lcd.setCursor(0,2); lcd.print("[3]Manual");//Columna,Fila
    lcd.setCursor(0,3); lcd.print("[4]Automatico");//Columna,Fila  
  }  
  while(indio==1)
  {
    contador1=contador1+1;
    //Funcion de presentacion de variables
    if(contador1>4)
    {
      //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ambiente.read(22,&T,&H,NULL);
    tierra1.read(23,&T1,&H1,NULL);
    tierra2.read(24,&T2,&H2,NULL);
    humedad1= 1024-analogRead(0);
    humedad2= 1024-analogRead(1);
    //humedad1= 60+(analogRead(0)*100)/1024;
    //humedad2= 60+(analogRead(1)*100)/1024;
    luz1= 1024-analogRead(2);
    luz2= 1024-analogRead(3);
    contador1=0;
    }
    
    if(humedad1>900)
    humedad1=100;
    if(humedad1<0)
    humedad1=0;
    if(humedad2>900)
    humedad2=100;
    if(humedad2<0)
    humedad2=0;
    
    if(luz1<0)
    luz1=0;
    if(luz1>100)
    luz1=100;
    if(luz2<0)
    luz2=0;
    if(luz2>100)
    luz2=100;
    lcd.setCursor(0,0); lcd.print("TA[c]:    HA[%]:    ");//Columna,Fila 
    lcd.setCursor(0,1); lcd.print("T1[c]:    H1[%]:    ");//Columna,Fila
    lcd.setCursor(0,2); lcd.print("T2[c]:    H2[%]:    ");//Columna,Fila
    lcd.setCursor(0,3); lcd.print("L1[L]:    L2[L]:    ");//Columna,Fila  
    lcd.setCursor(6,0); lcd.print(String(T));
    lcd.setCursor(16,0);lcd.print(String(H));
    lcd.setCursor(6,1); lcd.print(String(T1));
    lcd.setCursor(16,1);lcd.print(String(humedad1));
    lcd.setCursor(6,2); lcd.print(String(T2));
    lcd.setCursor(16,2);lcd.print(String(humedad2));
    lcd.setCursor(6,3); lcd.print(String(luz1));
    lcd.setCursor(16,3);lcd.print(String(luz2));
    char key = keypad.getKey();
    if(key) {switch (key){case 'B': indio=0; lcd.clear();}}//Cuando key "B" es oprimida...
    delay(500);
    //Serial.println((int)T);
  }
  while(indio==2)
  {
    contador1=contador1+1;
    if(contador1>20)
    {
    //Funcion de presentacion de variables, nivel de agua, cuando no hay luz, riego o luz on/off
    if (digitalRead(nivel) == LOW)
    {
      lcd.setCursor(0,0);lcd.print("Nivel agua alto");
      lcd.setCursor(0,3);lcd.print("");
    }
    if (digitalRead(nivel) == HIGH)
    {
      lcd.setCursor(0,0);lcd.print("Nivel agua bajo");
      lcd.setCursor(0,3);lcd.print(" Alerta sonido");
      digitalWrite(sonido, HIGH);
      delay(200);  
      digitalWrite(sonido, LOW);  
      delay(200);  
    }
    contador1=0;
    }
    //luz1= 100-(analogRead(2)*100)/1024;
    //luz2= 100-(analogRead(3)*100)/1024;
    luz1= 1024-analogRead(2);
    luz2= 1024-analogRead(3);
    lcd.setCursor(0,1);lcd.print("Luz1:      Luz2:     ");
    if(luz1<=90)
    {
      lcd.setCursor(6,1);lcd.print("NG");
    }
    else
    {
      lcd.setCursor(6,1);lcd.print("OK");
    }
    if(luz2<=90)
    {
      lcd.setCursor(16,1);lcd.print("NG");
    }
    else
    {
      lcd.setCursor(16,1);lcd.print("OK");
    }
    lcd.setCursor(0,2);lcd.print("Rieg1:    Rieg2:    ");
    if(riego1==1)
    {
      lcd.setCursor(6,2);lcd.print("ON");
    }
    if(riego1==0)
    {
      lcd.setCursor(6,2);lcd.print("OFF");
    }
    if(riego2==1)
    {
      lcd.setCursor(16,2);lcd.print("ON");
    }
    if(riego2==0)
    {
      lcd.setCursor(16,2);lcd.print("OFF");
    }
    delay(500);
    char key = keypad.getKey();
    if(key) {switch (key){case 'B': indio=0; lcd.clear();}}//Cuando key "B" es oprimida...
  }
  while(indio==3)
  {
    //Se despliega el LCD con modo Riego Manual e iluminacion manual
    lcd.setCursor(0,0); lcd.print("[1]Riego Manual");//Columna,Fila 
    lcd.setCursor(0,1); lcd.print("[2]Ilumin. Manual");//Columna,Fila
    lcd.setCursor(0,2); lcd.print("[B]Regresar");//Columna,Fila
    
    char key = keypad.getKey();
    if(key) {switch (key){case '1': indio=31; lcd.clear();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '2': indio=32; lcd.clear();}}//Cuando key "B" es oprimida...
    delay(200);
    
    while(indio==31)//bombas y migra variable
    {
      if(riego1==1)
      digitalWrite(valvula1, LOW);
      if(riego1==0)
      digitalWrite(valvula1, HIGH);
      if(riego2==1)
      digitalWrite(valvula2, LOW);
      if(riego2==0)
      digitalWrite(valvula2, HIGH);
      lcd.setCursor(0,0); lcd.print("[1]Riego1 ON");//Columna,Fila
      lcd.setCursor(0,1); lcd.print("[2]Riego1 OFF");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("[3]Riego2 ON");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("[4]Riego2 OFF");//Columna,Fila
      char key = keypad.getKey();
      if(key) {switch (key){case 'B': indio=3; lcd.clear();}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '1': riego1=1; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '2': riego1=0; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '3': riego2=1; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '4': riego2=0; }}//Cuando key "B" es oprimida...
    }
    while(indio==32)// RGB Y migra variables
    {
      
      if(RGB1==1)
      {digitalWrite(R1, LOW);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);}
      if(RGB1==2)
      {digitalWrite(R1, HIGH);digitalWrite(G1, HIGH);digitalWrite(BB1, LOW);}
      if(RGB1==3)
      {digitalWrite(R1, HIGH);digitalWrite(G1, LOW);digitalWrite(BB1, HIGH);}
      if(RGB2==4)
      {digitalWrite(R2, LOW);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);}
      if(RGB2==5)
      {digitalWrite(R2, HIGH);digitalWrite(G2, LOW);digitalWrite(B2, HIGH);}
      if(RGB2==6)
      {digitalWrite(R2, HIGH);digitalWrite(G2, HIGH);digitalWrite(B2, LOW);}
      if(RGB2==7)
      {
        digitalWrite(R2, HIGH);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);
        digitalWrite(R1, HIGH);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);
      }
      lcd.setCursor(0,0); lcd.print("[1] R1 [2] G1 [3] B1");//Columna,Fila
      lcd.setCursor(0,1); lcd.print("[4] R2 [5] G2 [6] B2");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("PWM[%]:    ");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("PWM[%]:    ");//Columna,Fila

      analogWrite(10,PWM1);
      
      contador1=contador1+1;
      if(contador1>5)
      {
      lcd.setCursor(8,2); lcd.print(String(PWM1));//Columna,Fila
      lcd.setCursor(8,3); lcd.print(String(PWM2));//Columna,Fila
      contador1=0;
      }
      char key = keypad.getKey();
      if(key) {switch (key){case 'B': indio=3; lcd.clear();}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '1': RGB1=1; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '2': RGB1=2; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '3': RGB1=3; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '4': RGB2=4; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '5': RGB2=5; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '6': RGB2=6; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case 'C': PWM1=PWM1+25;PWM2=PWM1; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case 'D': PWM1=PWM1-25;PWM2=PWM1; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': PWM1=255;PWM2=255; }}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '0': PWM1=0;PWM2=0; RGB2=7;}}//Cuando key "B" es oprimida...

      if(PWM1>255)
      {
      PWM1=0;
      PWM2=0;
      }
      if(PWM1<0)
      {
      PWM1=0;
      PWM2=0;
      }
      delay(200);
    }
    
    if(key) {switch (key){case 'B': indio=0; lcd.clear();}}//Cuando key "B" es oprimida...
  }

  while(indio==4)
  {
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    tierra1.read(23,&T1,&H1,NULL);
    tierra2.read(24,&T2,&H2,NULL);
    //humedad1= 60+(analogRead(0)*100)/1024;
    //humedad2= 60+(analogRead(1)*100)/1024;
    humedad1= 1024-analogRead(0);
    humedad2= 1024-analogRead(1);
    //TP1= (analogRead(6)*50)/1024;
    //TP2= (analogRead(7)*50)/1024;
       
    BUTP1=TP1;
    BUTP2=TP2;
    if(TP1<0)
    TP1=BUTP1;
    if(TP2<0)
    TP2=BUTP2;
    if(TP1>50)
    TP1=50;
    if(TP2>50)
    TP2=50;

    BUHP1=HP1;
    BUHP2=HP2;
    if(HP1<0)
    HP1=0;
    if(HP2<0)
    HP2=0;
    if(HP1>900)
    HP1=900;
    if(HP2>900)
    HP2=900;
   
    if(T1>TP1)
    {      digitalWrite(ventilador1,LOW);delay(100);    }
    else
    {       digitalWrite(ventilador1,HIGH);delay(100);  }
    if(T2>TP2)
    {      digitalWrite(ventilador2,LOW);delay(100);    }
    else
    {       digitalWrite(ventilador2,HIGH);delay(100);  }
    if(humedad1<HP1)
    {      digitalWrite(valvula1, LOW);delay(100);riego1=1;    }
    else
    {       digitalWrite(valvula1, HIGH);delay(100);riego1=0;  }
    if(humedad2<HP2)
    {      digitalWrite(valvula2, LOW);delay(100);riego2=1;    }
    else
    {       digitalWrite(valvula2, HIGH);delay(100);riego2=0;    }


    lcd.setCursor(0,0); lcd.print("T1[c]:    H1[%]:    ");//Columna,Fila
    lcd.setCursor(0,1); lcd.print("T2[c]:    H2[%]:    ");//Columna,Fila
    lcd.setCursor(6,0); lcd.print(String(T1));
    lcd.setCursor(6,1); lcd.print(String(T2));
    lcd.setCursor(16,0);lcd.print(String(humedad1));
    lcd.setCursor(16,1);lcd.print(String(humedad2));
    lcd.setCursor(0,2); lcd.print("TP1:      HP1:      ");//Columna,Fila
    lcd.setCursor(0,3); lcd.print("TP2:      HP2:      ");//Columna,Fila
    lcd.setCursor(6,2); lcd.print(String(TP1));//Columna,Fila
    lcd.setCursor(16,2); lcd.print(String(HP1));//Columna,Fila
    lcd.setCursor(6,3); lcd.print(String(TP2));//Columna,Fila
    lcd.setCursor(16,3); lcd.print(String(HP2));//Columna,Fila
    
    
    contador1=contador1+1;
    if(contador1>20)
    {
    if (digitalRead(nivel) == LOW)
    {
      //lcd.setCursor(8,3);lcd.print("Nivel alto");
    }
    if (digitalRead(nivel) == HIGH)
    {
      //lcd.setCursor(8,3);lcd.print("Nivel bajo");
      digitalWrite(sonido, HIGH);
      delay(200);  
      digitalWrite(sonido, LOW);  
      delay(200);  
    }
    
    contador1=0;
    }

    
    delay(200);
    char key = keypad.getKey();
    if(key) {switch (key){case 'B': indio=0; lcd.clear();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '9': HP1=HP1+100; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '#': HP1=HP1-100; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case 'C': HP2=HP2+100; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case 'D': HP2=HP2-100; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '7': TP1=TP1+1; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '*': TP1=TP1-1; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '8': TP2=TP2+1; }}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '0': TP2=TP2-1; }}//Cuando key "B" es oprimida...
    
  }

while(indio==5)
  {
    lcd.setCursor(0,0); lcd.print("Trabajando...");//Columna,Fila
    digitalWrite(R1, LOW);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);
    delay(2000); 
    digitalWrite(R1, HIGH);digitalWrite(G1, HIGH);digitalWrite(BB1, LOW);
    delay(2000); 
    digitalWrite(R1, HIGH);digitalWrite(G1, LOW);digitalWrite(BB1, HIGH);
    delay(2000); 
    digitalWrite(R2, LOW);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);
    delay(2000);  
    digitalWrite(R2, HIGH);digitalWrite(G2, LOW);digitalWrite(B2, HIGH);
    delay(2000);  
    digitalWrite(R2, HIGH);digitalWrite(G2, HIGH);digitalWrite(B2, LOW);
    delay(2000); 
    digitalWrite(R1, HIGH);digitalWrite(G1, HIGH);digitalWrite(BB1, HIGH);
    digitalWrite(R2,HIGH);digitalWrite(G2, HIGH);digitalWrite(B2, HIGH);
    char key = keypad.getKey();
    if(key) {switch (key){case 'B': indio=0; lcd.clear();}}//Cuando key "B" es oprimida...
    
    indio=0;
  }
  
}

/*
1.- Monitor.- Se presenta en pantalla los datos LCD4X20(tiempo real)
    a) Temperatura y humedad ambiente
    b)Temperatura y humedad suelo planta1
    c) Temperatura y humedad suelo planta2
    d) Iluminación planta1 y planta2.
2.-Información
    Falta agua
    No hay Luz
    Riego encendido o apagado
    Luz encendida o apagada

3.- Trabaje en modo manual. 
   a)Riego Manual
         1)Encendido y apagado bomba1 de riego
         2 )Encendido y apagado bomba2 de riego
   b)Iluminación Manual
        1) Selección de color planta1(RGB) 
        1) Selección de color planta2(RGB)
        2) Control de PWM1 planta 1(perilla giratoria)
        2) Control de PWM2 planta 2 (perilla giratoria)

4.- Trabaje en modo Automatico(Preprogramada por usuario)
      1) Programacion de temperatura(>25°c).- Ventilador se enciende si la temperatura sobre pasa los valos especificados.

      2)Humedad.- Debe estar entre 60% y 80%(Nota: por lo general el sensor comunica si esta seco o humedo, y el valor seco es de 35% y el valor humedo es de 74%). Se activa riego cuando esta por debajo de la meta.

      3)Alertas.- Se presenta alerta sonora.
          Cuando no haya agua en el tanque.
        
*/
