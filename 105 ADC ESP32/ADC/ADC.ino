/*
 PLACA: NODE MCU 32S
 analogReadResolution(resolution): set the sample bits and resolution. 
It can be a value between 9 (0 – 511) and 12 bits (0 – 4095). 
Default is 12-bit resolution.
Nota:

analogSetWidth(width): set the sample bits and resolution. 
It can be a value between 9 (0 – 511) and 12 bits (0 – 4095). 
Default is 12-bit resolution.
Nota:Como si fuesen mas leds en pantalla.

analogSetCycles(cycles): set the number of cycles per sample. 
Default is 8. Range: 1 to 255.
Nota:

analogSetSamples(samples): set the number of samples in the range. 
Default is 1 sample. It has an effect of increasing sensitivity.
Nota:

analogSetClockDiv(attenuation): set the divider for the ADC clock. 
Default is 1. Range: 1 to 255.
Nota:

analogSetAttenuation(attenuation): sets the input attenuation for all ADC pins. 
Default is ADC_11db. Accepted values:

ADC_0db: sets no attenuation. ADC can measure up to approximately 
800 mV (1V input = ADC reading of 1088).

ADC_2_5db: The input voltage of ADC will be attenuated, 
extending the range of measurement to up to approx.
 1100 mV. (1V input = ADC reading of 3722).

ADC_6db: The input voltage of ADC will be attenuated, 
extending the range of measurement to up to approx. 
1350 mV. (1V input = ADC reading of 3033).

ADC_11db: The input voltage of ADC will be attenuated, 
extending the range of measurement to up to approx. 
2600 mV. (1V input = ADC reading of 1575).

Nota: Depende rango del sensor analogico 




analogSetPinAttenuation(pin, attenuation): 
sets the input attenuation for the specified pin. 
The default is ADC_11db. Attenuation values are the same from 
previous function.
Nota: resolucion para pin especifico.

adcAttachPin(pin): Attach a pin to ADC 
(also clears any other analog mode that could be on). 
Returns TRUE or FALSE result.
Nota:

adcStart(pin), adcBusy(pin) and resultadcEnd(pin): starts an ADC 
convertion on attached pin’s bus. 
Check if conversion on the pin’s ADC bus is currently running 
(returns TRUE or FALSE). 
Get the result of the conversion: returns 16-bit integer.
Nota:
 
*/

// the setup function runs once when you press reset or power the board


int sensorValue = 36;  // variable to store the value coming from the sensor

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  analogSetWidth(12);
  analogSetPinAttenuation(36, ADC_11db);
  
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Hola John");
  delay(1000);                       // wait for a second
  //digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("Dios te bendiga");
  delay(1000);                       // wait for a second

  sensorValue = analogRead(36);
  Serial.println("Valor: "+String(sensorValue) );
  delay(1000);                      
  
}
