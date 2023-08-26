#include <Keypad.h>
long tiempo;
int contador=0;
int enable=0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
{
 {1,2,3,0},
 {4,8,12,0},
 {16,20,24,0},
 {'*',0,'#',24}
};
byte rowPins[ROWS] = {11,10,9,8}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {7,6,5,4}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() 
{
  Serial.begin(9600);   
  pinMode(2, OUTPUT); //Motor 1
  pinMode(3, OUTPUT); //Motor 2
  pinMode(13, OUTPUT); //Motor 2
  digitalWrite(2, LOW);//salidas digitsles
  digitalWrite(3, LOW);//salidas digitsles
  digitalWrite(13, LOW);//salidas digitsles
}
void loop() 
{
  char key = keypad.getKey();
  if(key) 
  {
    switch (key)
    {   
      case '*':                                   
      Serial.println("Boton *");//El monitor serial escribe "ElectroCrea.com"
      digitalWrite(2, LOW);//salidas digitsles
      digitalWrite(3, HIGH);//salidas digitsles
      delay(300);
      digitalWrite(2, LOW);//salidas digitsles
      digitalWrite(3, LOW);//salidas digitsles
      
      break;
    }
  }
  if(key) 
  {
    switch (key)
    {   
      case '#':                            //Cuando key "A" es oprimida...          
      Serial.println("Boton #");   //El monitor serial escribe "ElectroCrea.com"
      digitalWrite(2, HIGH);//salidas digitsles
      digitalWrite(3, LOW);//salidas digitsles
      delay(300);
      digitalWrite(2, LOW);//salidas digitsles
      digitalWrite(3, LOW);//salidas digitsles
      break;
    }
  }
  if(key) 
  {   
      enable=1;
      tiempo= key*3600;
      Serial.print("Tiempo=");   //El monitor serial escribe "ElectroCrea.com"
      Serial.println(tiempo);   //El monitor serial escribe "ElectroCrea.com"
      digitalWrite(13, HIGH);//salidas digitsles
      delay(1000);
      digitalWrite(13, LOW);//salidas digitsles
      delay(400);
      digitalWrite(13, HIGH);//salidas digitsles
      delay(1000);
      digitalWrite(13, LOW);//salidas digitsles
      contador=0;
  }
  contador=contador+1;
  if ((contador>tiempo)&&(enable==1))
  {
      Serial.println("Boton B");   //El monitor serial escribe "ElectroCrea.com"
      digitalWrite(2, HIGH);//salidas digitsles
      digitalWrite(3, LOW);//salidas digitsles
      delay(3000);
      digitalWrite(2, LOW);//salidas digitsles
      digitalWrite(3, LOW);//salidas digitsles
  }
  delay(1000);
  Serial.print(contador);
  Serial.print(":");
  Serial.println(tiempo);
}

