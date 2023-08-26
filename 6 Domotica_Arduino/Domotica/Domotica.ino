int option='a';
int led = 13;
int centinela;
int sensor = 0;
int salida = 0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
}

void loop()
{
  //si existe datos disponibles los leemos
  if (Serial.available()>0)
  {
    //leemos la opcion enviada
    option=Serial.read();
    
    if(option=='a') 
    {
      digitalWrite(led, HIGH);              // ACTIVA RELAY DE LA PUERTA
      delay(1000);
      digitalWrite(led, LOW);               // DESACTIVA RELAY DE LA PUERTA Y PROTEGE SELENOIDE
      delay(100);
      Serial.println("(ok1)"); // ENVIA MENSAJE A TELEFONO
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      Serial.println("(ok1)");
      centinela = 0;                        // DESSACTIVA ALARMA
    }
    if(option=='c') 
    {
      digitalWrite(led, HIGH);              // ACTIVA RELAY DE LA PUERTA
      delay(1000);
      digitalWrite(led, LOW);               // DESACTIVA RELAY DE LA PUERTA Y PROTEGE SELENOIDE
      delay(100);
      Serial.println("(ok2)"); // ENVIA MENSAJE A TELEFONO
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      Serial.println("(ok2)");
      centinela = 0;                        // DESSACTIVA ALARMA
    }
    if(option=='b') 
    {
      centinela = 1;
      Serial.println(" SISTEMA EN ALERTA "); // ENVIA MENSAJE A TELEFONO
    }
  }
  sensor = analogRead(A0);
  salida = map(sensor, 0, 1023, 0, 255); 
  //Serial.println(sensor);
  if (option=='b')
  {
    if(salida>100)
    {
      Serial.println("int");
    }
  }
  delay(1000);
  
  
  
  
}
