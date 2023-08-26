#include<Wire.h>
#include"RTClib.h"
RTC_DS1307 RTC;
void setup()
{
  Wire.begin();//IniciaelpuertoI2C
  RTC.begin();//InicialacomunicaciónconelRTC
  //RTC.adjust(DateTime(__DATE__,__TIME__));//Establecelafechayhora(Comentarunavezestablecidalahora)
  Serial.begin(115200);//Establecelavelocidaddedatosdelpuertoserie
}
void loop()
{
  DateTime now = RTC.now();//ObtienelafechayhoradelRTC
  Serial.print(now.year(),DEC);//Año
  Serial.print("/");
  Serial.print(now.month(),DEC);//Mes
  Serial.print("/");
  Serial.print(now.day(),DEC);//Dia
  Serial.print(" ");
  Serial.print(now.hour(),DEC);//Horas
  Serial.print(":");
  Serial.print(now.minute(),DEC);//Minutos
  Serial.print(":");
  Serial.print(now.second(),DEC);//Segundos
  //Serial.println(now.dayOfWeek(),DEC);
  Serial.println();
  delay(1000);//Lainformaciónseactualizacada1seg.
}
