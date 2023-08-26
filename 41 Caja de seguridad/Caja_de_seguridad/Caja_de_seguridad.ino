#include <Keypad.h>
//Las variables utilizadas para la utilizacion del teclado 
const byte ROWS = 4;
const byte COLS = 4;
int validacion=0;
int clave=0;
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
int led = 13;
////////////////////////////////////////////////////////////////////VOID SETUP
void setup()
{
  //Inicializcion de comunicacion serial, pero no se usa computadora
  Serial.begin (9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);             
}
//Proceso inicial
void loop()
{
  //funcion que detecta una tecla presionada
  char key = keypad.getKey();
  /////////////////////////////////////////
  if(key) 
  {
    switch (key)
    {     
        case '1':                            //Cuando key "1" es oprimida...          
          clave=1;
          Serial.println("1");              //El monitor serial se escribe 1 
          digitalWrite(led, LOW);             //El sonido se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El sonido se enciende
          delay(200);
          validacion=validacion+1;          //Utilizado para presionar maximo 3 teclas
    }
  }
///////////////////////////////////////////////////////////////////////El siguiente bloque espera por la tecla 2
  if(key) 
  {
    switch (key)
    {     
        
        case '2':                            //Cuando key "2" es oprimida...          
          clave=2;
          Serial.println("2");                //El monitor serial escribe "ElectroCrea.com"
          digitalWrite(led, LOW);             //El led se apaga
          delay(200);
          digitalWrite(led, HIGH);             //El led se enciende
          delay(200);
          validacion=validacion+1;            El siguiente bloque espera por la tecla 2
    }
  }
/////////////////////////////////////////////////////////El siguiente bloque espera por la tecla 3
if(key) 
  {
    switch (key)
    {     
        case '3':                             //Cuando key "3" es oprimida...          
          clave=3;
          Serial.println("3");                //El monitor serial escribe numero 3
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);            //El led se enciende
          delay(200);
          validacion=validacion+1;
    }
  }
///////////////////////////////////////////////////El siguiente bloque, se valida el teclado segun la clave programada
  if(validacion==3)
  {
    validacion=0;
    if(clave==3)
    {
      Serial.println("clave exitosa");
      delay(1000);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
      digitalWrite(led, LOW);             //El led se enciende
      delay(500);
      
      digitalWrite(led, HIGH);             //El led se enciende
      delay(500);
    }
    else
    {
      while(1)
      {
          digitalWrite(led, HIGH);             //El led se enciende
          delay(200);
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
        }  
    }
    
  }
/////////////////////////////////////////////////////////
if(key) 
  {
    switch (key)
    {     
        case '4' :                            //Cuando key "4" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }
if(key) 
  {
    switch (key)
    {     
        case '5' :                            //Cuando key "A" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }
if(key) 
  {
    switch (key)
    {     
        case '6' :                            //Cuando key "6" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }
if(key) 
  {
    switch (key)
    {     
        case '7' :                            //Cuando key "7" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '8' :                            //Cuando key "8" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '9' :                            //Cuando key "9" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }
  if(key) 
  {
    switch (key)
    {     
        case '0' :                            //Cuando key "0" es oprimida...          
          Serial.println("otro");   
          digitalWrite(led, LOW);             //El led se enciende
          delay(200);
          digitalWrite(led, HIGH);             //El led se apaga
          delay(200);
          validacion=validacion+1;
    }
  }

}
//Es importante denotar que para cambiar la clave se debe de hacer un proceso de validaciones de variables
//par evitar errores

