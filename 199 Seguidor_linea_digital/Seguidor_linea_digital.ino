int motor1A = 2; //Cables para control del motor derecho
int motor1B = 3; //Cables para control del motor derecho
int motor2A = 4; //Cables para control del motor izquierdo
int motor2B = 5;  //Cables para control del motor izquierdo

/////////////Sensores
int sensor1=7;
int sensor2=8;

///////////// PWM
int PotenciaMB=175;
int PotenciaMA=175;

//////////////Cables que tranmiten la potencia
int PinPotenciaMA=9;
int PinPotenciaMB=10;

//////////////variable para lectura de los estados del los dos sensores de color Blanco/Negro
int buttonState1 = 0; 
int buttonState2 = 0; 

//////////////Variable para recibir comandos de control por simulacion
int dato=0;


////////////////////////Configuracion Principal
void setup() 
{
  Serial.begin(115200);     //Velocidad de tranmision de datos

  //Configuracion de los pines del Arduino como salida para control de Driver de los motores
  pinMode(motor1A, OUTPUT); 
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  //Configuracion de los pines del Arduino como apagado osea LOW = 0 voltios
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);

  //Instalacion de sensores infrarrojos, configurados como datos que van a ingresar al Arduino UNO osea INPUT
  pinMode(sensor2, INPUT);
  pinMode(sensor1, INPUT);
  
}

//Cuerpo de proyecto
void loop() 
{
  int buttonState1 = digitalRead(sensor1);  //Lectura del estado del sensor 1
  int buttonState2 = digitalRead(sensor2);  //Lectura del estado del sensor 2
  analogWrite(PinPotenciaMA,PotenciaMA);    //Asignacion de PWM para potencia a 175 del total de 255 como maximo para el motor A
  analogWrite(PinPotenciaMB,PotenciaMB);    //Asignacion de PWM para potencia a 175 del total de 255 como maximo  para el motor B
  
  // Toma de estados segun la lectura de los sensores

  //Adelante
  if ((buttonState1 == LOW) && (buttonState2 == LOW))
  {     
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
     
  }
  //parar
  if ((buttonState1 == HIGH) && (buttonState2 == HIGH))
  {
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,LOW);
      
  }
  
  //Izquierda
  if((buttonState1 == HIGH) && (buttonState2 == LOW))
  {
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,HIGH);
    digitalWrite(motor2B,LOW);
       
  }

  //Derecha
  if((buttonState1 == LOW) && (buttonState2 == HIGH))
  {
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,HIGH);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
        
  }
  
  //Pruebas por comunicacion serial
  if(Serial.available()>0)
  {
    dato=Serial.read();
  }
  if(dato=='w')
  {
    Serial.println("Adelante");
  }
  if(dato=='x')
  {
    Serial.println("Atras");
  }
  if(dato=='s') 
  {
    Serial.println("Parar");
  }
  if(dato=='a')
  {
    Serial.println("Izquierda");
  }
  if(dato=='d')
  {
    Serial.println("derecha");
  }
  dato=0;
  delay(10);
}

/*
 * if(Serial.available()>0)
  {
    dato=Serial.read();
  }
  if(dato=='w')
  {
    Serial.println("Adelante");
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
  }
  if(dato=='x')
  {
    Serial.println("Atras");
  }
  if(dato=='s') 
  {
    Serial.println("Parar");
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,LOW);
  }
  if(dato=='a')
  {
    Serial.println("Izquierda");
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,HIGH);
    digitalWrite(motor2B,LOW);
  }
  if(dato=='d')
  {
    Serial.println("Derecha");
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,HIGH);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
  }
  dato=0;
  delay(10);
 */
