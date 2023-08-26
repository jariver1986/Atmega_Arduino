 
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
 
void setup()
{
pinMode(sensorDeFlujo, INPUT);
pinMode(13, OUTPUT);
Serial.begin(9600);
digitalWrite(val1, HIGH);
digitalWrite(val2, HIGH);
attachInterrupt(0, flujo, RISING); // Setup Interrupt
digitalWrite(13, HIGH);
 

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
     digitalWrite(13, LOW);
    }
    if(option=='2') 
    {
     digitalWrite(13, HIGH);
    }
    
  }
  delay(10000); 

    //Serial.print(" Caudal: ");
    Serial.print(litrosPorHora, DEC); // Cantidad en litros por hora
    //Serial.print(" L/hour");
    //Serial.print(" - Pulsos totales: ");
    //Serial.print(pulsosAcumulados);    
    litros = pulsosAcumulados*1.0/400; //Cada 400 pulsos = 1 litro
    //Serial.print("  - Litros acumulados: ");
    Serial.print(";");
    Serial.println(litros);

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
//98:D3:31:70:7C:10
