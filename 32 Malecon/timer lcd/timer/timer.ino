#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int horas = 0;
int minutos = 0;
int segundos = 0;
int decimas = 0;
long milisegundos = 0;
int boton = 10;
int pausa = 9;

void setup(){
  Serial.begin(9600);
  pinMode(boton, INPUT);
  digitalWrite(boton, LOW);
  pinMode(pausa, INPUT);
  digitalWrite(pausa, LOW);
  lcd.begin(16,2);
}
void loop(){
  //Restart button
  if(digitalRead(boton) == HIGH){
    horas = 0;
    minutos = 0;
    segundos = 0;
    decimas = 0;
    lcd.clear();
  }
  //Pause/Play button
  if(digitalRead(pausa) == HIGH){
    delay(200);
    while(digitalRead(pausa) == LOW);
    delay(200);
  }
  milisegundos = millis();
  if(milisegundos % 100 == 0){ //Only enter if it has passed tenth of a second
    decimas++;
    if(decimas == 10){ //When it has passed 10 tenths of a second it count one second
      decimas = 0;
      segundos++;
    }
    if(segundos == 60){ //When it has passed 60 seconds it count one minute
      segundos = 0;
      minutos++;
    }
    if(minutos == 60){ //When it has passed 60 minutes it count one hour
      minutos = 0;
      horas++;
    }
    //Print Time
    lcd.setCursor(0,0);
    if(horas < 10){
      lcd.print("0");
    }
    lcd.print(horas);
    lcd.print(":");
    lcd.setCursor(3,0);
    if(minutos < 10){
      lcd.print("0");
    }
    lcd.print(minutos);
    lcd.print(":");
    lcd.setCursor(6,0);
    if(segundos < 10){
      lcd.print("0");
    }
    lcd.print(segundos);
    lcd.print(":");
    lcd.setCursor(9,0);
    lcd.print(decimas);
  }
}

