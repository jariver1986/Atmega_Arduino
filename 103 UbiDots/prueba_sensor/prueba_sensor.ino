#include <SimpleDHT.h>

int pinDHT11 = 14;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(115200);
}

void loop() 
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11 with RAW bits...");
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, data)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  float decimal=0.0;
  decimal=(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]);
  Serial.println(decimal/10);
  Serial.println("");
  float dato= temperature+decimal/10;
  Serial.print("Sample OK: ");
  Serial.print(String(dato));
  Serial.print(" *C, ");
  
  Serial.print((int)humidity); Serial.println(" H");
  Serial.print("DECIMAL T: ");
  Serial.println(String(2*2*2*data[28]+2*2*data[29]+2*data[30]+data[31]));
  
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
