int motor1A = 2; //Cables para control del motor derecho
int motor1B = 3; //Cables para control del motor derecho
int motor2A = 4; //Cables para control del motor izquierdo
int motor2B = 5;  //Cables para control del motor izquierdo
int motor3A = 6; //Cables para control del motor derecho
int motor3B = 7; //Cables para control del motor derecho
int motor4A = 8; //Cables para control del motor izquierdo
int motor4B = 9;  //Cables para control del motor izquierdo


//////////////Variable para recibir comandos de control por simulacion
int dato=0;

//////////////////////////////////////////////
int j1=0;
int j2=0;
////////////////////////Configuracion Principal
void setup() 
{
  Serial.begin(115200);     //Velocidad de tranmision de datos

  //Configuracion de los pines del Arduino como salida para control de Driver de los motores
  pinMode(motor1A, OUTPUT); 
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor3A, OUTPUT); 
  pinMode(motor3B, OUTPUT);
  pinMode(motor4A, OUTPUT);
  pinMode(motor4B, OUTPUT);


  //Configuracion de los pines del Arduino como apagado osea LOW = 0 voltios
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);
  digitalWrite(motor3A,LOW);
  digitalWrite(motor3B,LOW);
  digitalWrite(motor4A,LOW);
  digitalWrite(motor4B,LOW);

  
}

//Cuerpo de proyecto
void loop() 
{  
  j1 = analogRead(A0);
  j2 = analogRead(A3);
  
  if(Serial.available()>0)
  {
    dato=Serial.read();
  }
  
  
  if((dato=='w')||(j1>500))
  {
    Serial.println("Adelante");
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,HIGH);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
    digitalWrite(motor3A,LOW);
    digitalWrite(motor3B,HIGH);
    digitalWrite(motor4A,LOW);
    digitalWrite(motor4B,HIGH);
  }
  if((dato=='x')||(j1<50))
  {
    Serial.println("Atras");
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,HIGH);
    digitalWrite(motor2B,LOW);
    digitalWrite(motor3A,HIGH);
    digitalWrite(motor3B,LOW);
    digitalWrite(motor4A,HIGH);
    digitalWrite(motor4B,LOW);
  }
  if((dato=='s')||((j1>50)&&(j1<500))&&((j2>50)&&(j2<500))) 
  {
    Serial.println("Parar");
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,LOW);
    digitalWrite(motor3A,LOW);
    digitalWrite(motor3B,LOW);
    digitalWrite(motor4A,LOW);
    digitalWrite(motor4B,LOW);
  }
  if((dato=='a')||(j2>500))
  {
    Serial.println("Derecha");
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,HIGH);
    digitalWrite(motor2A,HIGH);
    digitalWrite(motor2B,LOW);
    digitalWrite(motor3A,LOW);
    digitalWrite(motor3B,HIGH);
    digitalWrite(motor4A,HIGH);
    digitalWrite(motor4B,LOW);
  }
  if((dato=='d')||(j2<50))
  {
    Serial.println("Izquierda");
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
    digitalWrite(motor3A,HIGH);
    digitalWrite(motor3B,LOW);
    digitalWrite(motor4A,LOW);
    digitalWrite(motor4B,HIGH);
    
  }
  dato=0;
  Serial.println("J1 = "+ String(j1));
  Serial.println("J2 = "+ String(j2));
  delay(500);
}
