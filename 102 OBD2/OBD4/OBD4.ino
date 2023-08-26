#include<SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);  // RX; TX
char incomingbyte = '-'; // variable de datos Bluetooth
//Time
byte mySec = 0; byte myMin = 0; byte myHour = 0; byte myDate = 1; byte myMonth = 1; byte myYear = 17;
byte nastr = 0; int HA = 0;
int HB = 0; int rpm = 0; int Temp=0; int Volt=0; float vv=0;
float shotlong = -0.1;


void setup() 
{

delay(300); delay(1000);

BTSerial.begin(38400); //BLUETOOTH MASTER QUE SE CONECTA CON EL OBD2 38400
Serial.begin(9600); // BLUETOOTH QUE SE CONECTA CON LA APP 9600
delay(1000); 
nastrELM();
}//setup

void  nastrELM()
{
// //

AT_ELM("at i\r");
AT_ELM("at d\r"); AT_ELM("at z\r");
AT_ELM("at d\r"); AT_ELM("at at 1\r");
AT_ELM("at st 9\r"); AT_ELM("at e0\r");
AT_ELM("at sp 5\r");  //5-FAST INIT 10 AUTOMATIC
AT_ELM("at tp 5\r"); AT_ELM("at ib10\r"); AT_ELM("at dp\r");
 
AT_ELM("at st 19\r"); // 19 ->25 *4mc = 100mc
AT_ELM("at at 2\r");
AT_ELM("at st 25\r"); // 19 ->25 *4mc = 100mc nastr = 1;
BTSerial.flush();

// //
Serial.println("------end nastrELM  ");
}// end nastrELM


void loop()
{
Serial.println("\n------- loop -"); delay(50);
if (nastr == 0) nastrELM();
AT_ELM("at i\r"); //inicializandoELM !!! AT_ELM("at dp\r");
if (nastr == 0) nastrELM(); AT_ELM("at  rv\r"); AT_ELM("at i\r"); BTSerial.flush();
AT_ELM("01 14\r");
AT_ELM("01 00\r");
AT_ELM("01 05\r"); //Temperatura del refrigerante; A-40; 27-40=-13
AT_ELM("01 0F\r"); //Intake air temperature; A-40; 30-40=-10
AT_ELM("01  11\r"); //Posición  del acelerador; A*100/255; 37*100/255=14,51 %
AT_ELM("01 14\r");
AT_ELM("01 06\r"); // (В-128)*100/128 Short AT_ELM("01 14\r");
AT_ELM("01 07\r"); // (В-128)*100/128 Long
AT_ELM("01 0B\r"); //Presión del colector de admisión; A; 101
AT_ELM("01 10\r"); //Flujo de aire ((A*256)+B)/100
AT_ELM("01 14\r"); // A/200 : (B-128) * 100/128 (if B==$FF, sensor no usado)
AT_ELM("01 0C\r"); //Velocidad del motor; ((A*256)+B)/4 ; 0
AT_ELM("01 04\r"); //Carga nominal del motor: A*100/255;
AT_ELM("01 14\r"); // A/200 : (B-128) * 100/128 (if B==$FF, sensor no usado)
AT_ELM("01 15\r"); // AT_ELM("01 14\r");
}//loop


void AT_ELM (char bufIn[40])
{
long ttime = 0; int i = 0;
int j = 0;
char bufOut[40];
for(int j=0; j<39; j++) bufOut[j]='-'; BTSerial.print(bufIn);
ttime = millis();

while(incomingbyte !='>')
{
 
while (BTSerial.available() > 0)  //  verifica  si  el  puerto  esta disponible
{
incomingbyte = BTSerial.read(); // lee los datos del puerto bufOut[i++] = incomingbyte;
if (i >37) break;
}
if ( millis()-ttime >2000) break;
}
BTSerial.flush(); bufOut[i++]='\0'; incomingbyte ='-';

if(bufOut[0]=='N' && bufOut[1]=='O') { nastr = 0;
}

//recepcion y decodificacion de datos provenientes del OBD2
//ELM
if  ((bufOut[0]=='a'  &&  bufOut[1]=='t'  &&  bufOut[2]=='  ')  || (bufOut[0]=='0' && bufOut[1]=='1' && bufOut[2]==' '))
{
Serial.print("???"); nastr = 0;
} // Afinación !!!

if (bufOut[17]=='F' &&  bufOut[18]=='A' &&  bufOut[19]=='S')
{ Serial.println("F");
}

if (bufOut[0]=='E' && bufOut[1]=='L' && bufOut[2]=='M')
{ Serial.println("E");
}

if (bufOut[2]=='.' && bufOut[4]=='V')
{
Serial.print("  VOLT");
Volt=(((bufOut[0]-48)*100)+((bufOut[1]-48)*10)+(bufOut[3]-48));
} //12,0

if ( bufOut[1]=='.' &&  bufOut[3]=='V' )
{

} //13,0

//EBU
if (bufOut[0]=='4' && bufOut[1]=='1')
{

if (bufOut[3]=='0' && bufOut[4]=='5') // T OG
{
HA = Hex2ToByte (bufOut, 6); Temp=HA-40;
}

if (bufOut[3]=='0' && bufOut[4]=='6') //short
{
HA = Hex2ToByte (bufOut, 6);
 
shotlong = (float(HA)-128)*100/128; //shotlong = -1.66;

}

if (bufOut[3]=='0' && bufOut[4]=='7') //long
{
HA = Hex2ToByte (bufOut, 6); shotlong = (float(HA)-128)*100/128;
}

if (bufOut[3]=='0' && bufOut[4]=='C') //rpm
{
HA = Hex2ToByte (bufOut, 6); HB = Hex2ToByte (bufOut, 9); rpm = ((HA*256)+HB)/4;
}

if (bufOut[3]=='1' && bufOut[4]=='4') //rpm
{
HA = Hex2ToByte (bufOut, 6); shotlong = float(HA)/200;
}

if (bufOut[3]=='1' && bufOut[4]=='5') //rpm
{
HA = Hex2ToByte (bufOut, 6); shotlong = float(HA)/200;
}

}
vv=Volt/10.0; Serial.print(rpm); Serial.print(":"); Serial.print(Temp); Serial.print(":"); Serial.print(vv); Serial.print("\n");

}//AT_ELM

int Hex2ToByte (char buf[], byte n)//CONVERSION HEXADECIMAL A BYTE
{
int y=0;
if (buf[n]-'0' >16) { y = y + (buf[n]-('A' - 10)) << 4  ;}
if (buf[n]-'0' <16) { y = y + (buf[n]-'0') << 4 ;}
if (buf[n+1]-'0' >16) { y = y + buf[n+1]-('A' - 10);}
if (buf[n+1]-'0' <16) { y = y + buf[n+1]-'0';} return y;
}

// //
int freeRam () {
extern int heap_start, * brkval; int v;
return (int) &v - ( brkval == 0 ? (int) & heap_start : (int)
   brkval);
}
