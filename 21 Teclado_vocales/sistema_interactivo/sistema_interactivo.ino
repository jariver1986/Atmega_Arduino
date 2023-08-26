#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','E'},
 {'7','8','9','I'},
 {'*','0','U','O'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {5,4,3,2}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int led = 13;
////////////////////////////////////////////////////////////////////VOID SETUP
void setup()
{
  Serial.begin (9600);
  pinMode(led, OUTPUT);
}
////////////////////////////////////////////////////////////////////VOID LOOP
void loop()
{
  char key = keypad.getKey();
  /////////////////////////////////////////Boton A
  if(key) 
{
  switch (key)
    {
    
      case 'A':                            //Cuando key "A" es oprimida...          
      Serial.println("A");   //El monitor serial escribe "ElectroCrea.com"
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      break;
    }
}
/////////////////////////////////////////Boton B
if(key) 
{
      switch (key)
      {
      case 'E'://Cuando key "B" es oprimida...          
      Serial.println("E");//El monitor serial escribe "Visítanos"
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      break;
      }
}
/////////////////////////////////////////Números del 1 al 3
if(key) 
{
  switch (key)
  {
    case '1':        
      Serial.println("1");
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      break;
  }
}


///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '2':        
    Serial.println("2");
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '3':        
    Serial.println("3");
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '4':        
    Serial.println("4");
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '5':        
    Serial.println("5");
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '6':        
    Serial.println("6");
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '7':        
    Serial.println("7");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '8':        
    Serial.println("8");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '9':        
    Serial.println("9");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case 'I':        
    Serial.println("I");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case 'O':        
    Serial.println("O");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case 'U':        
    Serial.println("U");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
///////////////////////////////
if(key) 
{
    switch (key)
    {
    case '0':        
    Serial.println("0");
    digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
    break;
    }
}
}
