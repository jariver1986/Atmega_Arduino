int led = 2;
void setup () {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop () 
{
    int sensor = analogRead(A0);
    sensor = map (sensor, 0,1023,0,100);    
    Serial.println(sensor);
    digitalWrite(led,LOW); 
    if (sensor>10) 
    {
      digitalWrite(led,LOW);
      delay(1000);
      Serial.print("A");
      //Serial.println(sensor);
     delay(10000);
    }
    else
    {
      digitalWrite(led,HIGH);
    }
    delay(3000);
}
  
  
