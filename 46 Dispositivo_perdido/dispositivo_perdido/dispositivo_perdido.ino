//Variables para control de motores
int option;
int out2 = 13;
int contador=0;


//Inicio de configuraciones
void setup()
{
  Serial.begin(9600);//comunicacion con el computador
  pinMode(out2, OUTPUT); //Motor 2
}
void loop()
{
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
  }
    if(option=='1') //Funcion que controla carro para ADELANTE
    {
      digitalWrite(out2, LOW);//salidas digitsles
      delay(1000);
      option=0;//listo para recibir comando
      contador=0;
    }
   if(option==0)
    {contador=contador+1;
      }
  
  Serial.print("2");
  delay(10);
  if(contador>5)
  {
    digitalWrite(out2, HIGH);//salidas digitsles
    
    }
}
