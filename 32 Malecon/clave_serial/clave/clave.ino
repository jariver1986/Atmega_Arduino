
int incomingByte = 0;   // for incoming serial data
int dato=0;
int dato1=0;
int dato2=0;
int dato3=0;
int dato4=0;
int dato5=0;
int dato6=0;
int dato7=0;
int dato8=0;
int dato9=0;
int total=0;
int turno=0;
String chaine = "";
long milisegundos = 0;
int option;
long dec=0;
int conteo=0;
int sonido   =13;

void setup() 
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps 
  pinMode(sonido,OUTPUT);
  digitalWrite(sonido,LOW);
                  
}

void loop() 
{
    while(turno==0)
    { 
      if (Serial.available() > 0) 
      {
                incomingByte = Serial.read();
                char fromSerial = incomingByte;
                if (fromSerial != 4) 
                {
                  chaine = chaine + fromSerial;
                }  
                  if(chaine[4]==57)
                { 
                  turno=1;
                }
      }  
    }
    while(turno==1)    
    {
     total= (chaine[0]-48)*1000+(chaine[1]-48)*100+(chaine[2]-48)*10+(chaine[3]-48);
     Serial.println(total);
     String chaine = "";
     turno=2;
    }    
  while(turno==2)    
    {
              if (Serial.available()>0)
              {
                option=Serial.read();
              }
                if(option=='B')
                {
                      conteo=1;
                }
                if(option=='S')
                {
                      milisegundos=0;
                      dec=0;
                      option=0;
                      conteo=0;
                      turno=0;
                }
                if(conteo==1)
                {
                      milisegundos = millis();
                      if(milisegundos%100==0)
                      {
                       dec++; 
                       
                      }
                }
                
               if(dec==total )
                {
                  digitalWrite(sonido,HIGH);
                  delay(100);
                  digitalWrite(sonido,LOW);
                  Serial.println("LISTO ");
                  Serial.println(dec);
                  Serial.println(total);
                  milisegundos=0;
                  dec=0;
                  option=0;
                }
    }    
    
  
}


