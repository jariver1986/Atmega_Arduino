
long milisegundos = 0;
int option;
long dec=0;
int conteo=0;
void setup(){
  Serial.begin(9600);

}
void loop(){

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
            conteo=0;
      }
      if(conteo==1)
      {
            milisegundos = millis();
            if(milisegundos%100==0)
            {
             dec++; 
             
            }
      }
      
     if(dec==1150 )
      {
        Serial.println("LISTO");
        milisegundos=0;
        dec=0;
        option=0;
      }
  
  
}

