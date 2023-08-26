#include<Wire.h>
#include"RTClib.h"
RTC_DS1307 RTC;
void setup()
{
  Wire.begin();//IniciaelpuertoI2C
  RTC.begin();//InicialacomunicaciónconelRTC
  RTC.adjust(DateTime(__DATE__,__TIME__));//Establecelafechayhora(Comentarunavezestablecidalahora)
  Serial.begin(115200);//Establecelavelocidaddedatosdelpuertoserie
}
void loop()
{
  Serial.print("Hora configurada con fecha de compilacion de .hex");
  delay(1000);
}
