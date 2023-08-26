int valvula1=2;
int sensor1=0;
void setup () 
{
    Serial.begin(9600);  
    pinMode(valvula1,OUTPUT); 
    Serial.begin(9600);
    digitalWrite(valvula1, LOW);
}
void loop () 
{
    sensor1= 105-(analogRead(0)*100)/1000;
    if(sensor1>50)
    {
    digitalWrite(valvula1, LOW);
    }
    if(sensor1<50)
    {
    digitalWrite(valvula1, HIGH);
    }
    //Serial.println(sensor1);
    //digitalWrite(valvula1, HIGH);
    //delay(2500);  
    //digitalWrite(valvula1, LOW);
    //delay(2500);  
}
