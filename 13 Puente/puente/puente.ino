//------------------------------------
//Declara puertos de entradas y salidas
//------------------------------------
int pulsador1=2;        //Pin donde se encuentra el pulsador, entrada
int pulsador2=4;
int relay1   =12;            //Pin donde se encuentra el relay de salida.
int relay2   =13;            //Pin donde se encuentra el relay de salida.
int relay3 =7;            //Pin donde se encuentra el relay de salida.
int relay4 =8;            //Pin donde se encuentra el relay de salida.


//------------------------------------
//Funcion principal
//------------------------------------
void setup() // Se ejecuta cada vez que el Arduino se inicia
{
 pinMode(pulsador1, INPUT); //Configurar el pulsador como una entrada
 pinMode(pulsador2, INPUT); //Configurar el pulsador como una entrada
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
 
   //Condicional para saber estado del pulsador
   if (digitalRead(pulsador1)==HIGH)
   {
     //GIRO HACIA DELANTE
     digitalWrite(relay1,LOW);
     digitalWrite(relay2,HIGH);
     digitalWrite(relay3,LOW);
     digitalWrite(relay4,HIGH);
   }
   else
   {
     if (digitalRead(pulsador2)==HIGH)
     {
        //GIRO HACIA ATRAS
         digitalWrite(relay1,HIGH);
         digitalWrite(relay2,LOW);
         digitalWrite(relay3,HIGH);
         digitalWrite(relay4,LOW);
     }  
     else
     {
         //MOTOR PARAR
         digitalWrite(relay1,LOW);
         digitalWrite(relay2,LOW);
         digitalWrite(relay3,LOW);
         digitalWrite(relay4,LOW);
     }
   }
   
}
 
//Fin programa
