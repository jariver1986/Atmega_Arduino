#include <Mouse.h>              //Libreria para mouse.
#include <LiquidCrystal_I2C.h>  //Libreria para control de LCD.
#include <Wire.h>               //Libreria complemento para control de protocolo i2C.
#include <String.h>             //Libreria para manejo de cadena de caracteres.
#include <Keypad.h>             //Libreria para teclado 4x4.

//////////////////Asignacion de conexiones de teclado con arduino//////////
     byte fila[]    = {11, 10, 9, 8};    //Pines filas teclado 4x4
     byte columna[] = { 7, 6, 5, 4};     //Pines columnas teclado 4x4
     char teclas [ 4][ 4 ] =
          {
              {'1','2','3','A'},         // Grafica de teclado 4x4
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
          
//////////////////Configuracion teclado//////////////////////////////////////
Keypad teclado = Keypad(makeKeymap(teclas), fila, columna, 4, 4); 

//////////////////Configuracion LCD /////////////////////////////////////////
LiquidCrystal_I2C lcd(0x27,20,4); // LCD

/////////////////////////Configuracion de Joystick///////////////////////////
const int mouseLeftButton   = 12;      // Pin del boton izquierdo del mouse
const int mouseRightButton  = 13;      // Pin del boton derecho del mouse
const int joystickX         = A1;      // Pin para joystick arriba
const int joystickY         = A0;      // Pin para joystick abajo
/////////////////////////////////////////////////////////////////////////////
int     cursorSpeed     = 10;               // output speed of X or Y movement
int     responseDelay   = 5;                // response delay of the mouse, in ms
int     threshold       = cursorSpeed/4;    // resting threshold
int     center          = cursorSpeed/2;    // resting position value
boolean mouseIsActive   = false;            // whether or not to control the mouse
int     lastSwitchState = LOW;              // previous switch state

//////////////////////////Mensajes en LCD y aplicacion///////////////////////
String m1 = "Hola                                   .";
String m2 = "Hola buenos dias me ayuda repitiendo aquella parte, no entiendo     .";
String m3 = "Hola buenas tardes me ayuda repitiendo aquella parte, no entiendo   .";
String m4 = "Hola buenas noches me ayuda repitiendo aquella parte, no entiendo   .";
String m5 = "Disculpe ingeniero me permite salir de la clase un momento .";
String m6 = "Ingeniero no me sale el codigo, me puede ayudar            .";
String m7 = "Que calificacion obtuve en su materia                      .";
String m8 = "Que cambios deberia de realizar en este codigo             .";
String m9 = "Que deberia de realizar en esta pregunta                   .";
String m0 = "No entiendo                            .";
String mf = "@_;_";

///////////////////////////Prodedimiento para imprimir mesajes en pantalla LCD
void imprime(String palabra)
{
      for (int i = 0; i <= 19; i++)                 // recorre las 20 primeras posiciones de la fila 1
      {
        lcd.setCursor(i, 0);lcd.print(palabra[i]);  //Posiciona cursor e imprime caracter por caracter
        delay(1);                                   //retardo de 1 milisegundo
      }
      for (int i = 0; i <= 19; i++)                   // recorre las 20 primeras posiciones de la fila 2
      {
        lcd.setCursor(i, 1);lcd.print(palabra[i+20]); //Posiciona cursor e imprime caracter por caracter
        delay(1);                                     //retardo de 1 milisegundo
      }
      for (int i = 0; i <= 19; i++)                     // recorre las 20 primeras posiciones de la fila 3
      {
        lcd.setCursor(i, 2);lcd.print(palabra[i+20+20]);//Posiciona cursor e imprime caracter por caracter
        delay(1);                                       //retardo de 1 milisegundo
      }
      for (int i = 0; i <= 19; i++)                         // recorre las 20 primeras posiciones de la fila 4
      {
        lcd.setCursor(i, 3);lcd.print(palabra[i+20+20+20]); //Posiciona cursor e imprime caracter por caracter
        delay(1);                                           //retardo de 1 milisegundo
      }
}


////////////////////////Configuracion General/////////////////////
void setup() 
{
  Serial1.begin(9600);               // Inicio de comunicacion con antena Bluetooth
  pinMode(mouseLeftButton, INPUT);   // Seteo de Pin de boton izquierdo del mouse como entrada
  pinMode(mouseRightButton, INPUT);  // Seteo de Pin de boton derecho del mouse como entrada
  Mouse.begin();                     // Control de mouse activado

  lcd.init();                       //Inicio de pantalla LCD
  lcd.backlight();                  //Enciende iluminacion de fondo de pantalla LCD

  /////////////////Presentacion de mensaje en pantalla LCD///////////////////
  lcd.setCursor(0, 0);lcd.print("Desarrollo de recur ");
  lcd.setCursor(0, 1);lcd.print("sos educativos de ");
  lcd.setCursor(0, 2);lcd.print("apoyo de bajo coste");
  lcd.setCursor(0, 3);lcd.print("para discapacitados");
}

/////////////////////////////////////Inicio de Proceso///////////////////////
void loop() 
{
  char pulsacion = teclado.getKey() ;     //Pregunta por alguna tecla presionada
  if(pulsacion =='A')                     //Presionaste la tecla A
  {
    mouseIsActive = true;                 //Activa mouse
  }
  if(pulsacion =='B')                     //Presionaste la tecla B
  {
    lcd.clear();                          //Borra pantalla
  }
  if(pulsacion =='C')                     // Presenta mensaje de bienvenida
  {
    lcd.setCursor(0, 0);lcd.print("Desarrollo de recur ");
    lcd.setCursor(0, 1);lcd.print("sos educativos de ");
    lcd.setCursor(0, 2);lcd.print("apoyo de bajo coste");
    lcd.setCursor(0, 3);lcd.print("para discapacitados");
  }
  if(pulsacion =='D')         //Presionaste la tecla D
  {
    mouseIsActive = false;    //Desactiva Mouse
  }
  if(pulsacion =='1')         //Presionaste la tecla 1
  {
    lcd.clear();
    imprime(m1);              //Envia mensaje 1
    Serial1.println("1@_;_");
  }
  if(pulsacion =='2')         //Presionaste la tecla 2
  {
    imprime(m2);              //Envia mensaje 2          
    Serial1.println("2@_;_");
  }
  if(pulsacion =='3')         //Presionaste la tecla 3
  {
    imprime(m3);              //Envia mensaje 3
    Serial1.println("3@_;_");
  }
  if(pulsacion =='4')         //Presionaste la tecla 4
  {
    imprime(m4);              //Envia mensaje 4
    Serial1.println("4@_;_");
  }
  if(pulsacion =='5')         //Presionaste la tecla 5
  {
    imprime(m5);              //Envia mensaje 5
    Serial1.println("5@_;_");
  }
  if(pulsacion =='6')         //Presionaste la tecla 6
  {
    imprime(m6);              //Envia mensaje 6
    Serial1.println("6@_;_");
  }
  if(pulsacion =='7')         //Presionaste la tecla 7
  {
    imprime(m7);              //Envia mensaje 7
    Serial1.println("7@_;_");
  }
  if(pulsacion =='8')         //Presionaste la tecla 8
  {
    imprime(m8);              //Envia mensaje 8
    Serial1.println("8@_;_");
  }
  if(pulsacion =='9')         //Presionaste la tecla 9
  {
    imprime(m9);              //Envia mensaje 9
    Serial1.println("9@_;_");
  }
  if(pulsacion =='0')         //Presionaste la tecla 0
  {
    imprime(m0);              //Envia mensaje 0
    Serial1.println("0@_;_");
  }
  if(pulsacion =='*')         //Presionaste la tecla *
  {
    Mouse.click();
  }
  if(pulsacion =='#')         //Presionaste la tecla #
  {
    Mouse.click(MOUSE_RIGHT);
  }
  
  int xReading = readAxis(A1);          //Obtiene coordenada de movimiento en X
  int yReading = readAxis(A0);          //Obtiene coordenada de movimiento en Y
  
  if (mouseIsActive) 
  {
    Mouse.move(xReading, yReading, 0);  // Mueve mouse segun coordenadas leidas
  }  

  
    /////////////////////////////////////////////////////// CLICK IZQUIERDO
  if (mouseIsActive) 
  {
    if (digitalRead(mouseLeftButton) == HIGH)   //Botonera izquierda presionada? 
    {
        Mouse.click();    //Click izquierdo
        delay(100);
    }

    
    /////////////////////////////////////////////////////// CLICK DERECHO
    if (digitalRead(mouseRightButton) == HIGH) //Botonera derecha presionada? 
    {
        Mouse.click(MOUSE_RIGHT); //Click derecho
        delay(100);
    }
   }
}

///////////Funcion para recorrer distancia con mouse
int readAxis(int thisAxis) 
{
  int reading = analogRead(thisAxis);
  reading = map(reading, 0, 1023, 0, cursorSpeed);
  int distance = reading - center;
  if (abs(distance) < threshold) 
  {
    distance = 0;
  }
  return distance;
}
