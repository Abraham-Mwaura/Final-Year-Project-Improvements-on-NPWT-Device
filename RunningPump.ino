/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
  int sensorValue=0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int potValue = analogRead(A0);
  potValue=map(potValue, 0,1023,0,255);
  // print out the value you read:
  Serial.print(potValue);
  Serial.print(" : ");
  analogWrite(6,potValue );
  analogWrite(7, 0);
  sensorValue= analogRead(A1);
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
