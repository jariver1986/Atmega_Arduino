  //Descacrga de libreria
  //http://playground.arduino.cc/Code/Keypad#Download
  
  #include <Keypad.h>   
     byte fila[] = {9, 8, 7, 6};     
     byte columna[] = { 5, 4, 3, 2};     
     
     char teclas [ 4][ 4 ] =
          {
              {'1','2','3','A'},
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
     Keypad teclado = Keypad(makeKeymap(teclas), fila, columna, 4, 4);
 
     void setup()
        {             
          Serial.begin(9600) ; 
        }

     void loop()
        {       
          char pulsacion = teclado.getKey() ;
          if (pulsacion != 0)              
          Serial.print(pulsacion);   
        }
