int motor1A = 2;
int motor1B = 3;
int motor2A = 4;
int motor2B = 5;
int PinPotenciaMA=9;
int PotenciaMA=175;
int PinPotenciaMB=10;
int PotenciaMB=175;

int dato=0;

void adelante()
{
  analogWrite(PinPotenciaMA,PotenciaMA);
  analogWrite(PinPotenciaMB,PotenciaMB);
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,HIGH);
}
void atras()
{
  analogWrite(PinPotenciaMA,PotenciaMA);
  analogWrite(PinPotenciaMB,PotenciaMB);
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,HIGH);
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor2B,LOW);
}
void derecha()
{
  analogWrite(PinPotenciaMA,PotenciaMA);
  analogWrite(PinPotenciaMB,PotenciaMB);
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor2B,LOW);
}

void izquierda()
{
  analogWrite(PinPotenciaMA,PotenciaMA);
  analogWrite(PinPotenciaMB,PotenciaMB);
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,HIGH);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,HIGH);
}
void parar()
{
  analogWrite(PinPotenciaMA,0);
  analogWrite(PinPotenciaMB,0);
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);
}
////////////////////////Configuracion Principal
void setup() 
{
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);

  //Instalacion de sensores infrarrojos
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  
}

//Cuerpo de proyecto
void loop() 
{
  int sensor1 = analogRead(0);
  int sensor2 = analogRead(1);

  Serial.println("Sensor1: " + String(sensor1));
  Serial.println("Sensor2: " + String(sensor2));
  
  // Lectura de sensores de color infrarrojo
  if((sensor2<200)&&(sensor1<200)) //Negro Negro
  {
    adelante();
    delay(10);
    Serial.println("Adelante");
  }
  if((sensor2<200)&&(sensor1>200))  //Negro Blanco
  {
    izquierda();
    delay(10);
    Serial.println("Izquierda");
  }   
  if((sensor2>200)&&(sensor1<200))  //Blanco Negro
  {
    derecha();
    delay(10);
    Serial.println("Derecha");
  }
  if((sensor2>200)&&(sensor1>200))  //Blanco Blanco
  {
    parar();
    delay(10);
    Serial.println("Parar");
  }
  

  
  //Pruebas por comunicacion serial
  if(Serial.available()>0)
  {
    dato=Serial.read();
  }
  if(dato=='w')
  {
    adelante();
  }
  if(dato=='x')
  {
    atras();
  }
  if(dato=='s') 
  {
    parar();
  }
  if(dato=='a')
  {
    izquierda();
  }
  if(dato=='d')
  {
    derecha();
  }
  dato=0;
  //delay(1000);
}
