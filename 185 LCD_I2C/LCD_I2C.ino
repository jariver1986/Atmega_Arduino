
//https://www.google.com/maps?q=-2.220492,-79.886967
#include <LCD_I2C.h>
#include <Keypad.h>   

//////////gps
//#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
//SoftwareSerial serialgps(4,3); //RX,TX
int year;
byte month,day,hour,minute,second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
char dato=' ';
int centinela=0;
//////////

///////////////////LCD
LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according


/////////////////TECLADO
     byte fila[] = {12, 11, 10, 9};     
     byte columna[] = { 8, 7, 6, 5};     
     
     char teclas [ 4][ 4 ] =
          {
              {'1','2','3','A'},
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
     Keypad teclado = Keypad(makeKeymap(teclas), fila, columna, 4, 4);
 
void setup()
{
    ///////////////////LCD
    lcd.begin();
    lcd.backlight();
    lcd.print("Proyecto"); // You can make spaces using well... spaces
    lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
    lcd.print("Seguridad");
    delay(1000);

    ////////////////////gps
    Serial.begin(115200);
    Serial1.begin(9600);
}

void loop()
{
    char pulsacion = teclado.getKey() ;
    if (pulsacion != 0)              
    Serial.println("Teclado: " + String(pulsacion));
    
    
    if(pulsacion == '1')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lat: -79.886967 "); // You can make spaces using well... spaces
      lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
      lcd.print("Lon: -2.220492  ");
      Serial.println("Datos GPS: -79.886967 ; -2.220492 ");

    }
    if(pulsacion == '2')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mensaje alerta"); // You can make spaces using well... spaces
      lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
      lcd.print("Enviado");
      Serial.println("MENSAJE DE ALERTA ENVIADO");
    }
    if(pulsacion == 'A')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Desarrollador#1:"); // You can make spaces using well... spaces
      lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
      lcd.print("Franciso G.");
      
    }
    if(pulsacion == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Desarrollador#2:"); // You can make spaces using well... spaces
      lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
      lcd.print("Hidalgo S.");
      
    }
    while(Serial1.available())
    {
        int c=Serial1.read();
        if(gps.encode(c))
        {
            //float latitude, longitude;
            //gps.f_get_position(&latitude, &longitude);
            //Serial.println(String(latitude,5)+String(longitude,5)+"@");
            Serial.print(c);
            //lcd.setCursor(0, 0);
            //lcd.print(latitude);
            //lcd.setCursor(0, 1);
            //lcd.print(longitude);
            delay(50);
        }
    }
}
