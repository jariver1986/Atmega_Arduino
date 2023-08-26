//declaracion de variables  
float sensor =0;
float sensor2 =0;

// Inicializacion de pines 
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT); // ventilador de climatizacion
  pinMode(11, OUTPUT); 
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT); 
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
}
void loop()
{
  //Lectura de temperatura
  sensor =(analogRead(A5)*48875)/100000;

  //Convierte a Farenheit
  sensor2 = ((sensor*9)/5)+32;


  // Envio de dato serial al PC
  Serial.print("T Centigrados = ");
  Serial.print(sensor);
  Serial.print("C");
  Serial.println();
  Serial.print("T Farenheit = ");
  Serial.print(sensor2);
  Serial.print("F"); 

  //Imprime nueva linea
  Serial.println();Serial.println();

  //Condiciones
  if((sensor>20)&&(sensor<=25))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);
  }  
  if((sensor>25)&&(sensor<=30))
  {
    digitalWrite(11,HIGH);
    delay(750);
    digitalWrite(11,LOW);
    delay(750);
    digitalWrite(11,HIGH);
    delay(750);
    digitalWrite(11,LOW);
    delay(750);
  }  
  if((sensor>30)&&(sensor<=35))
  {
    digitalWrite(10,HIGH);
    delay(500);
    digitalWrite(10,LOW);
    delay(500);
    digitalWrite(10,HIGH);
    delay(500);
    digitalWrite(10,LOW);
    delay(500);
  }  
  if((sensor>35)&&(sensor<40))
  {
    digitalWrite(9,HIGH);
    delay(250);
    digitalWrite(9,LOW);
    delay(250);
    digitalWrite(9,HIGH);
    delay(250);
    digitalWrite(9,LOW);
    delay(250);
  }  
  if(sensor>=40)
  {
    digitalWrite(12,LOW);
  }  
  else
  {
    digitalWrite(12,HIGH);
  }
  delay(1000);
}

