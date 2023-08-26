     //Libreria para lectura de datos de ELM
#include <LiquidCrystal_I2C.h> //Libreria para control de LCD
#include <Wire.h>           //Libreria complemento para control de protocolo i2C
#include <String.h>         //Libreria para manejo de cadena de caracteres


LiquidCrystal_I2C lcd(0x27,20,4); // LCD

String datogps="0000000000000000";   
int year;
byte month,day,hour,minute,second, hundredths;
int ds = -77;
String incomingString="";
void setup()
{

  Serial.begin(115200);  //Consola
  pinMode(13, OUTPUT); //LUZ VERDE
  digitalWrite(13, HIGH);//LUZ VERDE
  
  lcd.init();
  lcd.backlight();
  //Display Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("IoT");
  lcd.setCursor(0, 1);
  lcd.print("Bienvenido");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO.");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO..");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO...");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("CONECTANDO....");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura[C]:");
  lcd.setCursor(10, 1); 
  lcd.print(ds);
  
  
}

void loop()
{
    if (Serial.available() > 0) {
    // read the incoming string:
    incomingString = Serial.readStringUntil('@');
    datogps=incomingString;
    // prints the received data
    Serial.print("He recibido: ");
    Serial.println(incomingString);
    
    lcd.setCursor(0, 0);
    lcd.print("Temperatura[C]:");
    if(isDigit(datogps[2])&&isDigit(datogps[3])&&isDigit(datogps[5])&&isDigit(datogps[6])){
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Temperatura[C]:");
      lcd.setCursor(8, 1); lcd.print(datogps[2]); //PRESENTACION DE DATOS DE LONGITUD
      lcd.setCursor(9, 1); lcd.print(datogps[3]);
      lcd.setCursor(10, 1); lcd.print(datogps[4]);
      lcd.setCursor(11, 1); lcd.print(datogps[5]);
      lcd.setCursor(12, 1); lcd.print(datogps[6]);
    }
  }
  
  
  delay(5000);
}
