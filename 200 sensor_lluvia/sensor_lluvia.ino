const int sensorPin = 3;
void setup() {
  Serial.begin(115200);   //iniciar puerto serie
  pinMode(sensorPin, INPUT);  //definir pin como entrada
}
 
void loop(){
  int value = 0;
  value = digitalRead(sensorPin );  //lectura digital de pin
 
  if (value == LOW) {
      Serial.println("Detectada lluvia");
  }
  delay(1000);
}
