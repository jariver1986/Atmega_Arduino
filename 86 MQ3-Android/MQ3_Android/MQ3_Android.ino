int dato=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(3, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(11, OUTPUT); 

  digitalWrite(3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(11,LOW);
  
}

void loop() 
{  
  if(Serial.available()>0)
  {
    dato=Serial.read();    
  }
  if(dato=='X')
  {
    int adc_MQ = analogRead(A0); //Lemos la salida analógica  del MQ
    float voltaje = adc_MQ * (5.0 / 1023.0); //Convertimos la lectura en un valor de voltaje
    float Rs=1000*((5-voltaje)/voltaje);  //Calculamos Rs con un RL de 1k
    double alcohol=(0.4091*pow(Rs/5463, -1.497))/10; // calculamos la concentración  de alcohol con la ecuación obtenida.
    //-------Enviamos los valores por el puerto serial------------
    Serial.print("_");
    Serial.print(alcohol,3);
    Serial.print("@");
    Serial.print(adc_MQ);
    Serial.print("@_@_@;_");

    if(adc_MQ<333)
    { 
      digitalWrite(3, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(8, LOW);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
    }
    if((adc_MQ>333)&&(adc_MQ<666))
    { 
      digitalWrite(3, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
    }
    if(adc_MQ>666)
    { 
      digitalWrite(3, LOW);
      digitalWrite(6, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
    }
    
    dato=0;
  }
}
