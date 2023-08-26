int led = 2;        // asigna a LED el valor 13
int boton = 3;       // asigna a botón el valor 7
int valor = 0;       // define el valor y le asigna el
int cent=0;
int envia=1;
                     // valor 0

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT); // configura el led (pin13) como salida
  pinMode(boton, INPUT); // configura botón (pin7) como entrada

}

void loop()
{


 
valor = digitalRead(boton); //lee el estado de la entrada botón
if(valor==HIGH)
  {
  
    digitalWrite(led,HIGH);   // envía a la salida 'led' el valor leído}
    delay(200);
    digitalWrite(led,LOW);   // envía a la salida 'led' el valor leído}
    delay(200);
    
  }
else
  {
    digitalWrite(led,LOW);   // envía a la salida 'led' el valor leído}
  }
if ((cent=1)and(envia=1) )
  {
  Serial.print("X");
  envia=0;
  }
}

