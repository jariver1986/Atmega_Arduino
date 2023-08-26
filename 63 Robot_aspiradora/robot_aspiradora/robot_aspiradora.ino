int dato=0;
int out4 = 10;
int out1 = 12;
int out3 = 11;
int out2 = 13;
int out5 =  9;
int option;

//Inicio de configuraciones
void setup()
{
  Serial.begin(9600);//comunicacion con el computador
  Serial1.begin(9600);//comunicacion con antena
  pinMode(out2, OUTPUT); //Motor 2
  pinMode(out4, OUTPUT); //Motor 4
  pinMode(out1, OUTPUT); //Motor 1
  pinMode(out3, OUTPUT); //Motor 3
  pinMode(out5, OUTPUT); //Motor 3
  digitalWrite(out5, HIGH);//salidas digitsles
}
void loop()
{
  if (Serial1.available()>0)
  {
    //leemos la opcion enviada
    option=Serial1.read();
    if(option=='1') //Funcion que controla carro para ADELANTE
    {
      digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      digitalWrite(out3, HIGH);//salidas digitsles
      digitalWrite(out4, LOW);//salidas digitsles
      option=0;//listo para recibir comando
    }
    if(option=='2') //Funcion que controla carro para //ATRAS
    {
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, HIGH);//salidas digitsles
      digitalWrite(out3, LOW);//salidas digitsles
      digitalWrite(out4, HIGH);//salidas digitsles
      option=0;//listo para recibir comando
    }
    if(option=='3') ////Funcion que controla carro para DERECHA
    {
      digitalWrite(out1, HIGH);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      digitalWrite(out3, LOW);//salidas digitsles
      digitalWrite(out4, HIGH);//salidas digitsles
      option=0;//listo para recibir comando
    }
    if(option=='4') ////Funcion que controla carro para IZQUIERDA
    {
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, HIGH);//salidas digitsles
      digitalWrite(out3, HIGH);//salidas digitsles
      digitalWrite(out4, LOW);//salidas digitsles
      option=0;//listo para recibir comando
    }
     if(option=='5') ////Funcion que controla carro para IZQUIERDA
    {
      digitalWrite(out1, LOW);//salidas digitsles
      digitalWrite(out2, LOW);//salidas digitsles
      digitalWrite(out3, LOW);//salidas digitsles
      digitalWrite(out4, LOW);//salidas digitsles
      option=0;//listo para recibir comando
    }
    /*if((option=='6')&&(dato==0)) ////Funcion que controla carro para IZQUIERDA
    {
      digitalWrite(out5, LOW);//salidas digitsles
      dato=1;
      option=0;//listo para recibir comando
    }
    if((option=='6')&&(dato==1)) ////Funcion que controla carro para IZQUIERDA
    {
      digitalWrite(out5, HIGH);//salidas digitsles
      dato=0;
      option=0;//listo para recibir comando
    }*/
    if(option=='6') ////Funcion que controla carro para IZQUIERDA
    {
      digitalWrite(out5, LOW);//salidas digitsles
      delay(1000);
      digitalWrite(out5, HIGH);//salidas digitsles
      option=0;//listo para recibir comando
    }
    
  }
  
}
