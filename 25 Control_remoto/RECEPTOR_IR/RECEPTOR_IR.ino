#include <IRLib.h>

int RECV_PIN = 11;
IRrecv My_Receiver(RECV_PIN);

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];
#define prender  0xE0E020DF//coloca el codigo de tu control
#define apagar   0xE0E0A05F//coloca el codigo de tu control

void setup()
{
  Serial.begin(9600);
  delay(2000);while(!Serial);//delay for Leonardo
  My_Receiver.enableIRIn(); 
  My_Decoder.UseExtnBuf(Buffer);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {
  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Receiver.resume(); 
    My_Decoder.decode();
    My_Decoder.DumpResults();
    Serial.println(My_Decoder.value,HEX);
    if(My_Decoder.value==prender) 
    {
     
    digitalWrite(13,HIGH);
    Serial.println("tecla numero 1");
    }
   if(My_Decoder.value==apagar) 
    { 
    digitalWrite(13,LOW);
    
    }
    if(My_Decoder.value==0xE0E0609F) //codigo de l contorl sin declarar
    { 
    digitalWrite(12,HIGH);
    
    }
    
  }
}

