#include <Keypad.h>
//Las variables utilizadas para la utilizacion del teclado 
const byte ROWS = 4;
const byte COLS = 4;
int validacion=0;
int clave=0;
int luz=0;
int tiempo1=0;
int tiempo2=0;
int contador=0;
int control=0;
//Teclado
char keys[ROWS][COLS] = 
{
 {'1','2','3','A'},
 {'4','5','6','E'},
 {'7','8','9','I'},
 {'*','0','U','O'}
};
//Ubicación de pines para la conexion arduino y teclado
byte rowPins[ROWS] = {9,8,7,6}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {5,4,3,2}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//Led hace de encendido y apagado de la alarmas
int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;

////////////////////////////////////////////////////////////////////VOID SETUP
void setup()
{
  //Inicializcion de comunicacion serial, pero no se usa computadora
  Serial.begin (9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led1, HIGH);             
  digitalWrite(led2, HIGH);             
  digitalWrite(led3, HIGH);             
  digitalWrite(led4, HIGH);             
  randomSeed(1);
}
//Proceso inicial
void loop()
{
  //funcion que detecta una tecla presionada
  char key = keypad.getKey();
  if(key) 
  {
    switch (key)
    {   case '1':                            //Cuando key "1" es oprimida...          
        digitalWrite(led1, HIGH);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '2':                            //Cuando key "1" es oprimida...          
        digitalWrite(led1, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '3':                            //Cuando key "1" es oprimida...          
        digitalWrite(led2, HIGH);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '4':                            //Cuando key "1" es oprimida...          
        digitalWrite(led2, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '5':                            //Cuando key "1" es oprimida...          
        digitalWrite(led3, HIGH);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '6':                            //Cuando key "1" es oprimida...          
        digitalWrite(led3, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '7':                            //Cuando key "1" es oprimida...          
        digitalWrite(led4, HIGH);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '8':                            //Cuando key "1" es oprimida...          
        digitalWrite(led4, LOW);             //El sonido se enciende
    }
  }
  if(key) 
  {
    switch (key)
    {   case '9':                            //Cuando key "1" es oprimida...          
         control=1;
    }
  }
 if(key) 
  {
    switch (key)
    {   case '0':                            //Cuando key "1" es oprimida...          
        digitalWrite(led1, HIGH);             
        digitalWrite(led2, HIGH);             
        digitalWrite(led3, HIGH);             
        digitalWrite(led4, HIGH);                   
        control=0;
    }
  }
  if(control==1)  
  {
    luz=random(10,13);
    tiempo1=random(1,5)*1000;
    tiempo2=random(1,5)*1000;
    digitalWrite(luz, LOW);             //El sonido se enciende
    delay(tiempo1);
    digitalWrite(luz,HIGH);             //El sonido se enciende
    delay(tiempo2);
    Serial.print("foco: ");
    Serial.println(luz);
    Serial.print("T1: ");
    Serial.println(tiempo1);
    Serial.print("T2 ");
    Serial.println(tiempo2);
    contador= contador+1;
    if (contador >4)
    {
      contador=0;
      digitalWrite(13, LOW);             //El sonido se enciende
      delay(tiempo1);
      digitalWrite(13,HIGH);             //El sonido se enciende
      delay(tiempo2);
      Serial.println("pin 13 ");
    }
   }
  
}

