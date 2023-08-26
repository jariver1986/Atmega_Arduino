//------------------------------------
//Declara puertos de entradas y salidas
//------------------------------------

int relay1   =12;            //Pin donde se encuentra el relay de salida.
int relay2   =13;            //Pin donde se encuentra el relay de salida.
int relay3 =7;            //Pin donde se encuentra el relay de salida.
int relay4 =8;            //Pin donde se encuentra el relay de salida.
int option;

//------------------------------------
//Funcion principal
//------------------------------------
void setup() // Se ejecuta cada vez que el Arduino se inicia
{
 Serial.begin(9600);
 pinMode(relay1,OUTPUT);      //Configurar el relay de salida 1
 pinMode(relay2,OUTPUT);      //Configurar el relay de salida 1
 pinMode(relay3,OUTPUT);      //Configurar el relay de salida 1
 pinMode(relay4,OUTPUT);      //Configurar el relay de salida 1
 digitalWrite(relay1,LOW);
 digitalWrite(relay2,LOW);
 digitalWrite(relay3,LOW);
 digitalWrite(relay4,LOW);
}
 
//------------------------------------
//Funcion ciclicla
//------------------------------------
void loop() // Esta funcion se mantiene ejecutando
{           //  cuando este energizado el Arduino
   if (Serial.available()>0)
  {
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,HIGH);
      digitalWrite(relay3,LOW);
      digitalWrite(relay4,HIGH);
    }
    if(option=='2') 
    {
         digitalWrite(relay1,HIGH);
         digitalWrite(relay2,LOW);
         digitalWrite(relay3,HIGH);
         digitalWrite(relay4,LOW);

    }
    if(option=='3') 
    {
         digitalWrite(relay1,LOW);
         digitalWrite(relay2,LOW);
         digitalWrite(relay3,LOW);
         digitalWrite(relay4,LOW);
    }
    if(option=='4') 
    {
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,HIGH);
      delay(200);
      digitalWrite(relay2,LOW);
    }
    if(option=='5') 
    {
      digitalWrite(relay3,LOW);
      digitalWrite(relay4,HIGH);
      delay(200);
      digitalWrite(relay4,LOW);
    }
  }
}
 
//Fin programa
