
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ---------------------- 
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
*/

//  Variables

int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int contador=0;
int centinela=0;
// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


void setup(){

  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  //Serial.begin(9600);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   
delay(10000);
}





void loop()
{
  
    serialOutput() ;       
    
  if (QS == true)
  {     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
        QS = false;                      // reset the Quantified Self flag for next time    
  }
     
  ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  delay(20);                             //  take a break
}

void mensaje()
{
  
  Serial.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000);
  Serial.println("AT+CMGS=\"0988930323\""); //0939536275//Numero al que vamos a enviar el mensaje
  delay(1000);
  Serial.println("Alerta peligro de infarto o el sensor esta mal colocado ");// Texto del SMS
  delay(100);
  Serial.println((char)26);//Comando de finalizacion ^Z
  delay(100);
  Serial.println();
  delay(5000); // Esperamos un tiempo para que envíe el SMS

  Serial.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000);
  Serial.println("AT+CMGS=\"0994449026\""); //0994449026  Numero al que vamos a enviar el mensaje
  delay(1000);
  Serial.println("Alerta peligro de infarto o el sensor esta mal colocado");// Texto del SMS
  delay(100);
  Serial.println((char)26);//Comando de finalizacion ^Z
  delay(100);
  Serial.println();
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  
}
void llamar()
   {
      Serial.println("AT");  //Comando AT para realizar una llamada
      delay(3000);
      Serial.println("ATD043092223;");  //Comando AT para realizar una llamada
      delay(10000);  // Espera 30 segundos mientras realiza la llamada
      Serial.println("ATH");  // Cuelga la llamada
      delay(3000);
      
   }



void ledFadeToBeat(){
    
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
    if ((BPM>60)&(BPM<=65))
    {
      //Serial.println(BPM);
      Serial.println("1");
    }
    if ((BPM>65)&(BPM<=70))
    {
      //Serial.println(BPM);
      Serial.println("2");
    }
    if ((BPM>70)&(BPM<=75))
    {
      //Serial.println(BPM);
      Serial.println("3");
    }
    if ((BPM>75)&(BPM<=80))
    {
      //Serial.println(BPM);
      Serial.println("4");
    }
    if ((BPM>80)&(BPM<=85))
    {
      //Serial.println(BPM);
      Serial.println("5");
    }
    if ((BPM>85)&(BPM<=90))
    {
      //Serial.println(BPM);
      Serial.println("6");
    }
    if ((BPM>90)&(BPM<=95))
    {
      //Serial.println(BPM);
      Serial.println("7");
    }
    if ((BPM>95)&(BPM<=100))
    {
      //Serial.println(BPM);
      Serial.println("8");
    }
    
    if (BPM>100)
    {
      contador=contador+1;
      if (contador>2)
      {
        
        contador=0;
        if(centinela==0)
        {
          mensaje();
          centinela=1;
        }
      }
    }
    //Serial.println(BPM);
    delay(2000);
    //Serial.print("AT+BAUD4");
    //Serial.print("\n");
    //delay(1000);
//llamar();
//mensaje();
//while(1)
{}
    
    
    
  }




