 
volatile int pulsos; // Cantidad de pulsos del sensor. Como se usa dentro de una interrupcion debe ser volatile
 
unsigned int litrosPorHora; // Calculated litres/hour
 
unsigned char sensorDeFlujo = 2; // Pin al que esta conectado el sensor
 
unsigned long tiempoAnterior; // Para calcular el tiempo
 
unsigned long pulsosAcumulados; // Pulsos acumulados
 
float litros; // Litros acumulados
int val1=3;
int val2=4;
void flujo () // Funcion de interrupcion
 
{
pulsos++; // Simplemente sumar el numero de pulsos
}
 
void setup()
{
pinMode(sensorDeFlujo, INPUT);
Serial.begin(115200);
digitalWrite(val1, HIGH);
digitalWrite(val2, HIGH);
attachInterrupt(0, flujo, RISING); // Setup Interrupt
 

interrupts(); // Habilitar interrupciones
tiempoAnterior = millis();
}
 
void loop ()
{
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='1') 
    {
      Serial.print(" VALVULA1 ENCENDIDA");
      digitalWrite(val1, LOW);
      option=0;
    }
    if(option=='2') 
    {
      Serial.print(" VALVULA1 APAGADA");
      digitalWrite(val1, HIGH);
      option=0;
    }
    if(option=='3') 
    {
      Serial.print(" VALVULA2 ENCENDIDA");
      digitalWrite(val2, LOW);
      option=0;
    }
    if(option=='4') 
    {
      Serial.print(" VALVULA2 APAGADA");
      digitalWrite(val2, HIGH);
      option=0;
    }
    
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
    Serial.print(litrosPorHora, DEC); // Cantidad en litros por hora
    Serial.print(" L/hour");
    Serial.print(" - Pulsos totales: ");
    Serial.print(pulsosAcumulados);
     
    litros = pulsosAcumulados*1.0/400; //Cada 400 pulsos = 1 litro
    Serial.print("  - Litros: ");
    Serial.println(litros);
    }
}
