
#include <Wire.h>      
#include <LiquidCrystal_I2C.h>      
      
#include <Keypad.h>
//#include <SimpleDHT.h>
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);//(RS,RE,D4,D5,D6,D7)
LiquidCrystal_I2C lcd(0x27,20,4);//(RS,RE,D4,D5,D6,D7)
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

//Variables
int indio=0;
int nivel=25;
int valvula1=26;//Riego1
int valvula2=27;//Riego2
int ventilador1=28;
int ventilador2=29;
int valvula3=30;
int sonido=36;
int contador1=0;
int contador2=0;
int contador3=0;
int contador4=0;
int segundo1=1000;
int segundo5=5000;
int segundo10=10000;
int segundo20=20000;
int segundo15=15000;
int segundo12=12000;
int segundo13=13000;

int dosis=0;
int cc1=1;
int cc5=5;
int cc20=20;
int cc6=6;
int cc4=4;
int cc100=100;
int cc10=10;
int cc8=8;
int cc25=25;
int cc15=15;
int cc13=13;

int cc12=12;
int limite1=100;
int centinela=-1;
int turno=0;
void alerta()
{
  digitalWrite(sonido, LOW);
  delay(200);  
  digitalWrite(sonido, HIGH);  
  delay(200);  
  }
void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  pinMode(nivel,INPUT);//NIVEL AGUA
  pinMode(valvula1,OUTPUT); 
  pinMode(valvula2,OUTPUT); 
  pinMode(ventilador1,OUTPUT); 
  pinMode(ventilador2,OUTPUT); 
  pinMode(valvula3,OUTPUT); 
  pinMode(sonido,OUTPUT); 
  digitalWrite(valvula1, LOW);  
  digitalWrite(valvula2, LOW);  
  digitalWrite(ventilador1, HIGH);  
  digitalWrite(ventilador2, HIGH); 
  digitalWrite(valvula3, LOW); 
  digitalWrite(sonido, HIGH);  
  alerta();  
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Purgando Lineas...");//Columna,Fila 
  //lcd.setCursor(0,1); lcd.print("Purgando Lineas...");//Columna,Fila 
  digitalWrite(valvula1, HIGH);
  delay(6000);
  digitalWrite(valvula1, LOW);
  delay(2000);
  digitalWrite(valvula2, HIGH);
  delay(6000);
  digitalWrite(valvula2, LOW);
  delay(2000);
  lcd.clear();
  alerta();  
  lcd.setCursor(0,0); lcd.print("[F1]Carbo Manual");//Columna,Fila 
  lcd.setCursor(0,1); lcd.print("[F2]Facial Program");//Columna,Fila
  lcd.setCursor(0,2); lcd.print("[F3]Corporal Program");//Columna,Fila
  lcd.setCursor(0,3); lcd.print("[F4]Cool-Lifting");//Columna,Fila  
  delay(1000);
}


void loop() 
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////INICIO
  char key = keypad.getKey();
  if(key) {switch (key){case 'A': indio=3;lcd.clear();alerta();}}//Cuando key "1" es oprimida...
  if(key) {switch (key){case 'B': indio=4;lcd.clear();alerta();}}//Cuando key "2" es oprimida...
  if(key) {switch (key){case 'C': indio=5;lcd.clear();alerta();}}//Cuando key "3" es oprimida...
  if(key) {switch (key){case 'D': indio=6;lcd.clear();alerta();}}//Cuando key "4" es oprimida...
  
  delay(50);
  if(indio==0)
  {
    lcd.setCursor(0,0); lcd.print("[F1]Carbo Manual");//Columna,Fila 
    lcd.setCursor(0,1); lcd.print("[F2]Facial Program");//Columna,Fila
    lcd.setCursor(0,2); lcd.print("[F3]Corporal Program");//Columna,Fila
    lcd.setCursor(0,3); lcd.print("[F4]Cool-Lifting");//Columna,Fila  
    delay(50);
  }
   /////////////////////////////////////// ///////////////////////////////////////////////////////////////////////////////F1CARBOMANUAL
   /////////////////////////////////////// ///////////////////////////////////////////////////////////////////////////////F1CARBOMANUAL
  while(indio==3)
  {
    lcd.setCursor(0,0); lcd.print("[1]Facial");//Columna,Fila 
    lcd.setCursor(0,1); lcd.print("[2]Corporal");//Columna,Fila
    lcd.setCursor(0,2); lcd.print("[Stop]Regresar");//Columna,Fila
    
    char key = keypad.getKey();
    if(key) {switch (key){case '1': indio=31; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '2': indio=32; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '#': indio=0; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    delay(200);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////F1F1
    //###########################################LCD
  }
    while(indio==31)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Facial         250cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=311;
    }
    while(indio==311)//bombas y migra variable
    {
     //###########################################PIE ABAJO
    if (digitalRead(nivel) == LOW)
    {
      centinela=-(centinela);
      alerta();
      delay(300);
    }
    //############################################
    if(centinela==1)
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc1;
      delay(segundo1);    
      lcd.setCursor(15,2); lcd.print(String(dosis));      
    }
    if(centinela==-1)
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");      
    }
    //###########################################LIMITACION
    if (dosis >=250)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=3; lcd.clear();alerta();contador1=0;dosis=0;indio=0;centinela=-1;digitalWrite(valvula1, LOW);}      }
      if(key) {switch (key){case '*': centinela=-(centinela); alerta(); delay(100);}}
    //###########################################
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////F1F2
    while(indio==32)// RGB Y migra variables
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Corporal      3000cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=322;
    }
      
    while(indio==322)// RGB Y migra variables
    {
    //############################################
    //###########################################PIE ABAJO
    if (digitalRead(nivel) == LOW)
    {
      centinela=-(centinela);
      alerta();
      delay(300);
    }
    //############################################
    //###########################################PIEABAJO 
    if (centinela==1)
    {
      digitalWrite(valvula2, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc5;
      delay(segundo1);
      lcd.setCursor(0,2); lcd.print("Dosis parcial: ");
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if (centinela==-1)
    {
      digitalWrite(valvula2, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
    }
    //###########################################
    //###########################################LIMITACION
    if (dosis >=3000)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
      
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=3; lcd.clear();alerta();contador1=0;dosis=0;indio=0;centinela=-1;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=-(centinela); alerta(); delay(100);}}
    //###########################################
    }  
  
   /////////////////////////////////////// //////////////////////////////////////////////////////////////////////////////////////////F2FACIALPROGRAM
   /////////////////////////////////////// ///////////////////////////////////////////////////////////////////////////////////////////F2FACIALPROGRAM
  while(indio==4)
  {
    if(turno<15)
    {
      lcd.setCursor(0,0); lcd.print("[1]Rejuvenecimiento ");//Columna,Fila 
      lcd.setCursor(0,1); lcd.print("[2]Capilar          ");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("[3]Cicatrices       ");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("[4]Papada           ");//Columna,Fila
    }
    if(turno>15)
    {
      lcd.setCursor(0,0); lcd.print("[5]Acne             ");//Columna,Fila 
      lcd.setCursor(0,1); lcd.print("[6]Post Operatorio  ");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("[7]Rosacea          ");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("                    ");//Columna,Fila
    }
    if(turno>30)
    {
      turno=0;
      }
    delay(300);
    turno=turno+1;
    char key = keypad.getKey();
    if(key) {switch (key){case '1': indio=41; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '2': indio=42; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '3': indio=43; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '4': indio=44; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '5': indio=45; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '6': indio=46; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '7': indio=47; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '#': indio=0; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
  }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-1-Rejuvenecimiento
    while(indio==41)//bombas y migra variable
    {
      lcd.clear();
        lcd.setCursor(0,0);lcd.print("Rejuvenecimiento 160");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=411;
    }
    while(indio==411)//bombas y migra variable
    {
      //###########################################PIE ABAJO
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc8;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIE ARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis >=160)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...   
      if(key) {switch (key){case '*': centinela=1; alerta();alerta(); delay(300);}}   
    //###########################################
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-2-Capilar
    while(indio==42)//bombas y migra variable
    {
      lcd.clear();
        lcd.setCursor(0,0);lcd.print("Capilar        200cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=422;
    }
    while(indio==422)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc10;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis >=200)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-3-Cicatrices
    while(indio==43)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Cicatrices      40cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=433;
    }
    
    while(indio==433)//bombas y migra variable
    {
      //###########################################PIE ABAJO
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc5;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIE ARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis >=40)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-4-Papada
    while(indio==44)//bombas y migra variable
    {
      lcd.clear();
        lcd.setCursor(0,0);lcd.print("Papada         200cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=444;
    }
    while(indio==444)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula2, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc20;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula2, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=200)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-5 Acne
    while(indio==45)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Acne           100cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=455;
    }
    while(indio==455)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc5;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=100)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
      
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=-(centinela); alerta(); delay(100);}}
    //###########################################
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-6 Post Operatoria
    while(indio==46)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Post Operatorio 60cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=466;
    }
    while(indio==466)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc6;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=60)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=-(centinela); alerta(); delay(100);}}
    //###########################################
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F2-7 Rosacea
    while(indio==47)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Rosacea         40cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=477;
    }
    while(indio==477)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula2, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc4;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula2, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=40)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }

/////////////////////////////////////// //////////////////////////////////////////////////////////////////////////////////////////////////F3CorporalProgram
/////////////////////////////////////// //////////////////////////////////////////////////////////////////////////////////////////////////F3CorporalProgram
while(indio==5)
  {
    if(turno<15)
    {
      lcd.setCursor(0,0); lcd.print("[1]Reduccion        ");//Columna,Fila 
      lcd.setCursor(0,1); lcd.print("[2]Celulitis        ");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("[3]Post Operatoria  ");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("[4]Estrias          ");//Columna,Fila
    }
    if((turno>15)&&(turno<30))
    {
      lcd.setCursor(0,0); lcd.print("[5]Cicatrices       ");//Columna,Fila 
      lcd.setCursor(0,1); lcd.print("[6]Acne Corporal    ");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("[7]Lesiones         ");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("   Microvasculares  ");//Columna,Fila
    }
    if(turno>30)
    {
      lcd.setCursor(0,0); lcd.print("[8]Rejuvenecimiento ");//Columna,Fila 
      lcd.setCursor(0,1); lcd.print("   Labios vaginales ");//Columna,Fila
      lcd.setCursor(0,2); lcd.print("                    ");//Columna,Fila
      lcd.setCursor(0,3); lcd.print("                    ");//Columna,Fila
    }
    if(turno>45)
    {
      turno=0;
      }
    delay(300);
    turno=turno+1;
    char key = keypad.getKey();
    if(key) {switch (key){case '1': indio=51; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '2': indio=52; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '3': indio=53; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '4': indio=54; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '5': indio=55; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '6': indio=56; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '7': indio=57; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '8': indio=58; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '#': indio=0; lcd.clear();alerta();}}//Cuando key "B" es oprimida...
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-1-Reduccion
    while(indio==51)//bombas y migra variable
    {
      lcd.clear();
        lcd.setCursor(0,0);lcd.print("Reduccion     1000cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=511;
    }
    while(indio==511)//bombas y migra variable
    {
      //###########################################PIE ABAJO
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula2, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc100;
      delay(segundo20);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIE ARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula2, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis >=1000)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-2-Celulitis
    while(indio==52)//bombas y migra variable
    {
      lcd.clear();
        lcd.setCursor(0,0);lcd.print("Celulitis      600cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=522;
    }
    while(indio==522)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula2, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc25;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula2, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis >=600)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-3-Post Operatorio
    while(indio==53)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Post Operatorio 100c");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=533;
    }
    
    while(indio==533)//bombas y migra variable
    {
      //###########################################PIE ABAJO
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc15;
      delay(segundo15);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIE ARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis >=100)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-4-Estrias
    while(indio==54)//bombas y migra variable
    {
      lcd.clear();
        lcd.setCursor(0,0);lcd.print("Estrias        100cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=544;
    }
    while(indio==544)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc12;
      delay(segundo12);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=100)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
    if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-5 Cicatrices
    while(indio==55)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Cicatrices     100cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=555;
    }
    while(indio==555)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc5;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=100)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-6 Acne Corporal
    while(indio==56)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Acne Corporal  208cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=566;
    }
    while(indio==566)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc13;
      delay(segundo13);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=208)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-7 Lesiones MIcrovasculares
    while(indio==57)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("L. Microvas.    60cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=577;
    }
    while(indio==577)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc6;
      delay(segundo5);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=60)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////F3-8 Vaginal
    while(indio==58)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Rej. Vaginal   100cc");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        lcd.setCursor(0,2); lcd.print("Dosis parcial: ");      
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=588;
    }
    while(indio==588)// RGB Y migra variables
    {
    //###########################################PIEABAJO 
    if ((digitalRead(nivel) == LOW)||(centinela==1))
    {
      digitalWrite(valvula1, HIGH);
      lcd.setCursor(0,1);lcd.print("Aplicando...");
      contador1= contador1+1;
      dosis=dosis+cc10;
      delay(segundo10);
      lcd.setCursor(15,2); lcd.print(String(dosis));
    }
    //###########################################PIEARRIBA
    if ((digitalRead(nivel) == HIGH))
    {
      digitalWrite(valvula1, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");
      centinela=-1;
    }
    //###########################################LIMITACION
    if (dosis>=100)
    {
      digitalWrite(valvula2, LOW);
      digitalWrite(valvula1, LOW);
      alerta();
      alerta();
      alerta();
      contador1=0;
      dosis=0;
      indio=0;
      lcd.clear();
    }
    //###########################################TECLADO
      char key = keypad.getKey();
      if(key) {switch (key){case '#': indio=4; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);}}//Cuando key "B" es oprimida...
      if(key) {switch (key){case '*': centinela=1; alerta(); delay(100);}}
    //###########################################
    }



/////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////F4Criolifting
/////////////////////////////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////F4Criolifting
    while(indio==6)//bombas y migra variable
    {
        lcd.clear();
        lcd.setCursor(0,0);lcd.print("Cool-Lifting        ");      
        lcd.setCursor(0,1);lcd.print("En pausa    ");   
        lcd.setCursor(0,3); lcd.print("[Stop]Regresar");//Columna,Fila  
        indio=66;
    }  
    while(indio==66)
    {
       //###########################################PIE ABAJO
      if (digitalRead(nivel) == LOW)
      {
          centinela=-(centinela);     
      }
      //###########################################PIE ARRIBA
      if(centinela==1)
      {
        digitalWrite(valvula3, HIGH);
        lcd.setCursor(0,1);lcd.print("Aplicando...");
        contador1= contador1+1;
        dosis=dosis+cc1;
        delay(segundo1); 
      }
      if(centinela==-1)
    {
      digitalWrite(valvula3, LOW);
      lcd.setCursor(0,1);lcd.print("En pausa    ");      
    }
      //###########################################LIMITACION
      if (dosis >=100)
      {
        digitalWrite(valvula3, LOW);
        lcd.setCursor(0,1);lcd.print("En pausa    ");
        alerta();
        alerta();
        alerta();
        contador1=0;
        dosis=0;
        indio=0;
        lcd.clear();
        centinela=-1;
      }
      //###########################################TECLADO
        char key = keypad.getKey();
        if(key) {switch (key){case '#': indio=3; lcd.clear();alerta();contador1=0;dosis=0;indio=0;turno=0;digitalWrite(valvula2, LOW);digitalWrite(valvula1, LOW);digitalWrite(valvula3, LOW);}}//Cuando key "B" es oprimida...
        if(key) {switch (key){case '*': centinela=-(centinela); alerta(); delay(100);}}
      //###########################################
    } 
}
