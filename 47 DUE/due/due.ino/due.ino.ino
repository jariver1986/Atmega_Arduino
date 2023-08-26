//+++++++++++++++++++++++++++++++++++++++++++++
//variable de recepcion de datos y cariables de control de elevacion
//+++++++++++++++++++++++++++++++++++++++++++++
int option;//Inicicializacion de variable
int led = 13;//Inicicializacion de variable
int contador=0;//Inicicializacion de variable
int contador2=85;//Inicicializacion de variable
int contador3=90;//Inicicializacion de variable
int inicio=0;//Inicicializacion de variable
int centinela=0;//Inicicializacion de variable
//+++++++++++++++++++++++++++++++++++++++++++++
  
void setup()
{
  Serial1.begin(9600);
}
  
void loop()
{
  Serial1.print("W");
  delay(1000);
}
//+++++++++++++FIN+++++++++++++++++++++++++++++
