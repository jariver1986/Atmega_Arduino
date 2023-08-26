#include <Keypad.h>

//Serial.print(" 20%:30%:40%:R1ON:R2OFF:R3OFF:HIGH:B1OFF:B2OFF;LOLA");
//Las variables utilizadas para la utilizacion del teclado 

const byte ROWS = 3;
const byte COLS = 3;
//Teclado
char keys[ROWS][COLS] = 
{
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
};
//Ubicación de pines para la conexion arduino y teclado
byte rowPins[ROWS] = {13,12,11}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {10,9,8}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int option=0;
int r1=0;
int r2=0;
int r3=0;
int b1=0;
int b2=0;
int tiempo=0;
int valvula1=2;
int valvula2=3;
int valvula3=4;
int bomba1=5;
int bomba2=6;
int nivel=7;
int tiempov1=0;
int tiempov2=0;
int tiempov3=0;
int key=0;

int sensor1=0;
int sensor2=0;
int sensor3=0;
void setup () 
{
    pinMode(valvula1,OUTPUT); 
    pinMode(valvula2,OUTPUT); 
    pinMode(valvula3,OUTPUT);     
    pinMode(bomba1,OUTPUT);     
    pinMode(bomba2,OUTPUT);     
    pinMode(nivel,INPUT);        
    Serial.begin(9600);
    digitalWrite(valvula1, LOW);
    digitalWrite(valvula2, LOW);
    digitalWrite(valvula3, LOW);
    digitalWrite(bomba1, LOW);
    digitalWrite(bomba2, LOW);
}
void loop () 
{
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(valvula1, HIGH);
      option=0;
      r1=1;
    }
    if(option=='2') 
    {
      digitalWrite(valvula1, LOW);
      option=0;
      r1=0;
    }
     if(option=='3') 
    {
      digitalWrite(valvula2, HIGH);
      option=0;
      r2=1;
    }
    if(option=='4') 
    {
      digitalWrite(valvula2, LOW);
      option=0;
      r2=0;
    }
    if(option=='5') 
    {
      digitalWrite(valvula3, HIGH);
      option=0;
      r3=1;
    }
    if(option=='6') 
    {
      digitalWrite(valvula3, LOW);
      option=0;
      r3=0;
    }
    if(option=='7') 
    {
      digitalWrite(bomba1, HIGH);
      option=0;
      b1=1;
    }
    if(option=='8') 
    {
      digitalWrite(bomba1, LOW);
      option=0;
      b1=0;
    }
    if(option=='9') 
    {
      digitalWrite(bomba2, HIGH);
      option=0;
      b2=1;
    }
    if(option=='A') 
    {
      digitalWrite(bomba2, LOW);
      option=0;
      b2=0;
    }
    ////////////////////////////////////////////
  }
  delay(250);

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
  tiempo=tiempo+1;
  delay(250);
  if (tiempo == 300)
  {
    tiempo=0;
    //Serial.print(" HUMEDAD1 = ");
    sensor1= (analogRead(0)*100)/1000;
    Serial.print(sensor1);
    Serial.print("%@");
    
    //Serial.print(":HUMEDAD2 = ");
    sensor2= (analogRead(1)*100)/1000;
    Serial.print(sensor2);
    Serial.print("%@");
  
    //Serial.print(":HUMEDAD3 = ");
    sensor3= (analogRead(2)*100)/1000;
    Serial.print(sensor3);
    if(r1==0) {Serial.print("%@OFF");}
    if(r1==1) {Serial.print("@ON");}
    if(r2==0) {Serial.print("@OFF");}
    if(r2==1) {Serial.print("@ON");}
    if(r3==0) {Serial.print("@OFF");}
    if(r3==1) {Serial.print("@ON");}
    if (digitalRead(nivel) == HIGH){Serial.print("@BAJO");}
    if (digitalRead(nivel) == LOW){Serial.print("@ALTO");}
    if(b1==0) {Serial.print("@OFF");}
    if(b1==1) {Serial.print("@ON");}
    if(b2==0) {Serial.print("@OFF");}
    if(b2==1) {Serial.print("@ON");}
    Serial.print("@");
    Serial.print(tiempov1);
    Serial.print("[s]@");
    Serial.print(tiempov2);
    Serial.print("[s]@");
    Serial.print(tiempov3);
    Serial.println("[s];P");
    
  }

////////////////////////////////////////////////////////////////////////////////////////
//NIVEL AGUA
    if (digitalRead(nivel) == HIGH)
    {
      b1=1;
      digitalWrite(bomba1, HIGH);
    }
    if (digitalRead(nivel) == LOW)
    {
      b1=0;
      digitalWrite(bomba1, LOW);
    }
  
////////////////////////////////////////////////////////////////////////////////////////
if(r1==1) 
{tiempov1=tiempov1+1;}
if(r2==1) 
{tiempov2=tiempov2+1;}
if(r3==1) 
{tiempov3=tiempov3+1;}
delay(250);
////////////////////////////////////////////////////////////////////////////////////////
//funcion que detecta una tecla presionada
  char key = keypad.getKey();
/////////////////////////////////////////

    
  
if(key) 
  {
    switch (key)
    {     
        case '2':                            //Cuando key "1" es oprimida...          
          digitalWrite(valvula1, LOW);             //El sonido se enciende
          r1=0;
    }
  }
 if(key) 
  {
    switch (key)
    {     
        case '1':                            //Cuando key "1" es oprimida...          
          digitalWrite(valvula1, HIGH);             //El sonido se enciende
          r1=1;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '4':                            //Cuando key "1" es oprimida...          
          digitalWrite(valvula2, LOW);             //El sonido se enciende
          r2=0;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '3':                            //Cuando key "1" es oprimida...          
          digitalWrite(valvula2, HIGH);             //El sonido se enciende
          r2=1;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '6':                            //Cuando key "1" es oprimida...          
          digitalWrite(valvula3, LOW);             //El sonido se enciende
          r3=0;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '5':                            //Cuando key "1" es oprimida...          
          digitalWrite(valvula3, HIGH);             //El sonido se enciende
          r3=1;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '8':                            //Cuando key "1" es oprimida...          
          digitalWrite(bomba2, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '7':                            //Cuando key "1" es oprimida...          
          digitalWrite(bomba2, HIGH);             //El sonido se enciende
    }
  }
  delay(250);
}
1700
