void setup() {
  
  Serial.begin(9600);
  analogReference(INTERNAL);
  //analogReference(INTERNAL1V1); //solo Arduino Mega
}

void loop() {
  
  float Irms=get_corriente(); //Corriente eficaz (A)
  float P=Irms*220.0; // P=IV (Watts)

  if (P<7.5)
  {
     
    Serial.println("0.00;0.00;1");   
    }
  if (P>7.5)
  {
    
    Serial.print(Irms,3);
    Serial.print(";");
    Serial.print(P,3);  
    Serial.print(";");
    Serial.println("1");
    }
  delay(10000);
  
  //Serial.print(" Potencia: ");
  //Serial.print(P,3);  
  //Serial.print("[W]");
  //Serial.print(";");
  //Serial.print(" Irms: ");
  //Serial.println(Irms,3);
  //Serial.println("[A]");
  //delay(100);     
}

float get_corriente()
{
  float voltajeSensor;
  float corriente=0;
  float Sumatoria=0;
  long tiempo=millis();
  int N=0;
  while(millis()-tiempo<500)//Duración 0.5 segundos(Aprox. 30 ciclos de 60Hz)
  { 
    voltajeSensor = analogRead(A0) * (1.1 / 1023.0);////voltaje del sensor
    corriente=voltajeSensor*30.0; //corriente=VoltajeSensor*(30A/1V)
    Sumatoria=Sumatoria+sq(corriente);//Sumatoria de Cuadrados
    N=N+1;
    delay(1);
  }
  Sumatoria=Sumatoria*2;//Para compensar los cuadrados de los semiciclos negativos.
  corriente=sqrt((Sumatoria)/N); //ecuación del RMS
  return(corriente);
}
