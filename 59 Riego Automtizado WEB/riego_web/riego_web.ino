//Trama de datos
//@@Humedad1@Humedad2@Humedad3@Humedad4@Humedad5@Selenoide1@Selenoide2@Selenoide3@Selenoide4@Selenoide5@Caudal@Acumulado
//@@56%@49%@44%@0%@0@OFF@OFF@OFF@OFF@OFF@0@0.00@


int r1=0;
int r2=0;
int r3=0;
int r4=0;
int r5=0;
int tiempo=0;

int valvula1=3;
int valvula2=4;
int valvula3=5;
int valvula4=6;
int valvula5=7;

int sensor1=0;
int sensor2=0;
int sensor3=0;
int sensor4=0;
int sensor5=0;
///////////////////////////////////////////////////////////////////
volatile int pulsos; // Cantidad de pulsos del sensor. Como se usa dentro de una interrupcion debe ser volatile
unsigned int litrosPorHora; // Calculated litres/hour
unsigned char sensorDeFlujo = 2; // Pin al que esta conectado el sensor
unsigned long tiempoAnterior; // Para calcular el tiempo
unsigned long pulsosAcumulados; // Pulsos acumulados
float litros; // Litros acumulados
int val1=3;
int val2=4;
int option=0;
void flujo () // Funcion de interrupcion
{
pulsos++; // Simplemente sumar el numero de pulsos
}
//////////////////////////////////////////////////////////////////
void setup () 
{
    pinMode(valvula1,OUTPUT); 
    pinMode(valvula2,OUTPUT); 
    pinMode(valvula3,OUTPUT);     
    pinMode(valvula4,OUTPUT);     
    pinMode(valvula5,OUTPUT);   
    pinMode(sensorDeFlujo, INPUT); 
    attachInterrupt(0, flujo, RISING); // Setup Interrupt
    interrupts(); // Habilitar interrupciones
    tiempoAnterior = millis(); 
     
    Serial.begin(9600);
    Serial1.begin(9600);
    digitalWrite(valvula1, HIGH);
    digitalWrite(valvula2, HIGH);
    digitalWrite(valvula3, LOW);
    digitalWrite(valvula4, LOW);
    digitalWrite(valvula5, HIGH);
//@@Humedad1@Humedad2@Humedad3@Humedad4@Humedad5@Selenoide1@Selenoide2@Selenoide3@Selenoide4@Selenoide5@Caudal@Acumulado
//    Serial.print("@@Humedad1@Humedad2@Humedad3@Humedad4@Humedad5@Selenoide1@Selenoide2@Selenoide3@Selenoide4@Selenoide5@Caudal[L/min]@Acumulado[Litros]");
}
void loop () 
{
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {
      digitalWrite(valvula1, LOW);
      option=0;
      r1=1;
    }
    if(option=='2') 
    {
      digitalWrite(valvula1, HIGH);
      option=0;
      r1=0;
    }
     if(option=='3') 
    {
      digitalWrite(valvula2, LOW);
      option=0;
      r2=1;
    }
    if(option=='4') 
    {
      digitalWrite(valvula2, HIGH);
      option=0;
      r2=0;
    }
    if(option=='5') 
    {
      digitalWrite(valvula3, HIGH);
      option=0;
      r3=1;
    }
    if(option=='6') 
    {
      digitalWrite(valvula3, LOW);
      option=0;
      r3=0;
    }
    if(option=='7') 
    {
      digitalWrite(valvula4, HIGH);
      option=0;
      r4=1;
    }
    if(option=='8') 
    {
      digitalWrite(valvula4, LOW);
      option=0;
      r4=0;
    }
    if(option=='9') 
    {
      digitalWrite(valvula5, LOW);
      option=0;
      r5=1;
    }
    if(option=='A') 
    {
      digitalWrite(valvula5, HIGH);
      option=0;
      r5=0;
    }
    ////////////////////////////////////////////
  }

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
  tiempo=tiempo+1;
  delay(1000);
  if (tiempo == 7)
  {
    tiempo=0;
    Serial.print("@@");
    sensor1= (analogRead(0)*100)/1000;
    Serial.print(105-sensor1);
    
    Serial.print("%@");
    sensor2= (analogRead(1)*100)/1000;
    Serial.print(105-sensor2);
  
    Serial.print("%@");
    sensor3= (analogRead(2)*100)/1000;
    Serial.print(105-sensor3);

    Serial.print("%@");
    sensor4= (analogRead(3)*100)/1000;
    Serial.print(105-sensor4);

    Serial.print("%@");
    sensor5= (analogRead(4)*100)/1000;
    Serial.print(105-sensor5);
    Serial.print("%");
    if(r1==0) {Serial.print("@OFF");}
    if(r1==1) {Serial.print("@ON");}
    if(r2==0) {Serial.print("@OFF");}
    if(r2==1) {Serial.print("@ON");}
    if(r3==0) {Serial.print("@OFF");}
    if(r3==1) {Serial.print("@ON");}
    if(r4==0) {Serial.print("@OFF");}
    if(r4==1) {Serial.print("@ON");}
    if(r5==0) {Serial.print("@OFF");}
    if(r5==1) {Serial.print("@ON");}
    Serial.print("@");
    //Serial.print("Caudal:");
    Serial.print(litrosPorHora, DEC); // Cantidad en litros por hora L/hour
    Serial.print("@");
    litros = pulsosAcumulados*1.0/400; //Cada 400 pulsos = 1 litro
    //Serial.print("Cantidad:");
    Serial.print(litros);
    Serial.println("@@");
  }
    
  // Cada segundo calcular e imprimir Litros/seg
  if( millis() - tiempoAnterior > 1000)
  {
      tiempoAnterior = millis(); // Updates cloopTime
      // Pulse frequency (Hz) = 6.67 Q, Q is flow rate in L/min. (Results in +/- 3% range)
      // Q = frecuencia / 6.67 (L/min)
      // Q = (frecuencia * 60) / 6.67 (L/hora)
      pulsosAcumulados += pulsos;
      litrosPorHora = (pulsos * 60 / 6.67); // (Pulse frequency x 60 min) / 7.5Q = flow rate in L/hour
      pulsos = 0; // Reset Counter
  }
}
