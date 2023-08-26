#include <LiquidCrystal_I2C.h>  //Libreria para control de LCD.
#include <Wire.h>               //Libreria complemento para control de protocolo i2C.
#include <String.h>             //Libreria para manejo de cadena de caracteres.
#include <Keypad.h>             //Libreria para teclado 4x4.

//////////////////Asignacion de conexiones de teclado con arduino//////////
     byte fila[]    = {9, 8, 7, 6};    //Pines filas teclado 4x4
     byte columna[] = { 5, 4, 3, 2};     //Pines columnas teclado 4x4
     char teclas [ 4][ 4 ] =
          {
              {'1','2','3','A'},         // Grafica de teclado 4x4
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
Keypad teclado = Keypad(makeKeymap(teclas), fila, columna, 4, 4); 
LiquidCrystal_I2C lcd(0x27,16,2); // LCD
int dato=0;
int contador =0;
int clave=1;

void setup() {
  Serial.begin(9600);
  lcd.init();                       //Inicio de pantalla LCD
  lcd.backlight();                  //Enciende iluminacion de fondo de pantalla LCD
  lcd.setCursor(0, 0);lcd.print("Sistema de");
    lcd.setCursor(0, 1);lcd.print("Seguridad");
  delay(2000);
  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1"); 
  delay(1000);
  
}
void llamada(){
  
  Serial.println("ATD+ +593961029793;"); //Declara el número a enviar sms
  delay(15000);  // Espera 20 segundos mientras realiza la llamada
  Serial.println("ATH");  // Cuelga la llamad
  delay(100); //Tiempo de retardo
  Serial.println(); //Salto de línea
  Serial.println("Fin......."); //Muestra mensaje por pantalla
}
void mensaje(){ 
  //Serial.println("Enviando SMS..."); //Muestra mensaje por pantalla
  Serial.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000); //Tiempo de retardo
  //SIM900.println("AT+CMGS=\"59394230466\""); //Numero al que vamos a enviar el mensaje
  Serial.println("AT+CMGS=\"593961029793\"");
  delay(1000); //Tiempo de retardo
  Serial.println("Alerta Intruso");// Texto del SMS
  Serial.println((char)26);//Comando de finalizacion
  delay(100); //Tiempo de retardo
  Serial.println(); //Muestra mensaje por pantalla
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  //Serial.println("SMS enviado Exitosamente");
}
void loop() 
{
  dato=analogRead(A0);
  //Serial.println(dato);  

  if(dato > 100)
  {lcd.clear();
    lcd.setCursor(0, 0);lcd.print("Alerta");
    lcd.setCursor(0, 1);lcd.print("Intruso");
    delay(2000);
    llamada();
    delay(2000);
    mensaje();
    lcd.clear();
    
  }

  char pulsacion = teclado.getKey() ;     //Pregunta por alguna tecla presionada
  if(pulsacion =='1') 
  {    
    contador++; 
    lcd.clear();
    lcd.setCursor(0, 0);lcd.print("Ingrese");
    lcd.setCursor(0, 1);lcd.print("Clave"); 
  }
  if(pulsacion =='2') { contador++;     }
  if(pulsacion =='3') { contador++;     }
  if(pulsacion =='4') { contador++;     }
  if(pulsacion =='5') { contador=contador+10;     }
  if(pulsacion =='6') { contador=contador+10;     }
  if(pulsacion =='7') { contador=contador+10;     }
  if(pulsacion =='8') { contador=contador+10;    }
  if(pulsacion =='9') { contador=contador+10;    }
  if(pulsacion =='0') { contador=contador+10;    }



  if (contador ==4)
  {
    lcd.clear();
      lcd.setCursor(0, 0);lcd.print("Acceso");
      lcd.setCursor(0, 1);lcd.print("Concedido");
      delay(2000);
      lcd.clear();
      contador=0;
  }
  if (contador >=40)
  {
    lcd.clear();
      lcd.setCursor(0, 0);lcd.print("Acceso");
      lcd.setCursor(0, 1);lcd.print("Negado");
      delay(2000);
      lcd.clear();
      contador=0;
  }
  delay(250);
}
