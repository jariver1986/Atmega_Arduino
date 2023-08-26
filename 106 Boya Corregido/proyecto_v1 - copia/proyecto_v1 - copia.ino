//variables bluetooth
int proporcion=0;
String sproporcion="";
int frecuencia=0;
String sfrecuencia="";
String bluetooth="";

//variables otr
int contador=0;
int tiempo=0;
int contadorPulsaciones = 0; 
int estadoPulsador = 0;    
int estadoAnteriorPulsador = 0;

//pines
const int rele=2;
const int boya=3;
const int buzzer=4;

void setup() {
  Serial.begin(9600);
  pinMode(rele,OUTPUT);
  pinMode(boya,INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  desactivacion_rele();
  delay(1000);
  medicion_boya();
  if(Serial.available()){
    bluetooth = Serial.readStringUntil('\n');
    Serial.print("bluetooth: ");
    Serial.println(bluetooth);
    for(int i=0;i<=3;i++){
      //proporcion string de 4
      sproporcion=sproporcion+bluetooth.charAt(i);
    }
    for(int i=4;i<=5;i++){
      //frecuencia string de 2
      sfrecuencia=sfrecuencia+bluetooth.charAt(i);
    }
    proporcion=sproporcion.toInt();
    frecuencia=sfrecuencia.toInt();
    Serial.print("proporcion: ");
    Serial.println(proporcion);
    Serial.print("frecuencia: ");
    Serial.println(frecuencia);    
    contadorPulsaciones=0;   
  }
  if(frecuencia == contadorPulsaciones && frecuencia !=0){
    contadorPulsaciones=0;
    activacion_rele();
    //bomba expulsa 12,52 ml x segundo
    tiempo=(proporcion/12.52)*1000;
    contador=contador+1;
    delay(tiempo);
    desactivacion_rele();
    if((1000/proporcion)-contador > 1 && (100/proporcion)-contador<2){
      contador=0;  
      digitalWrite(buzzer,HIGH);
      delay(250);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);
      delay(250);
      digitalWrite(buzzer,LOW);
    }
  } 
}

void medicion_boya(){
  estadoPulsador = digitalRead(boya);
  if (estadoPulsador != estadoAnteriorPulsador) {
    if (estadoPulsador == HIGH) {
      contadorPulsaciones++;
      Serial.print("numero de pulsaciones: ");
      Serial.println(contadorPulsaciones);
    }
  }
  estadoAnteriorPulsador = estadoPulsador;
}

void activacion_rele(){
  digitalWrite(rele,LOW);//En bajo se activa
}

void desactivacion_rele(){
  digitalWrite(rele,HIGH);//En alto se desactiva
}
