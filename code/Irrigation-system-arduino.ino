/* Smart Irrigation system based on arduino

*/

int sensorPin = A7;    // select the input pin for the potentiometer
int Pump = 2;

int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {

  Serial.begin(9600); // debug Console

  // declare the Pump pin as an OUTPUT:

  pinMode(Pump, OUTPUT);

}

void loop() {
  // read the value from the sensor:

  sensorValue = analogRead(sensorPin);// reads the value of the electrode (value between 0 and 1023)
  sensorValue = map(sensorValue, 0, 1023, 0, 15);     // scale it for use (value between 0 and 15)


  Serial.print(" Moister level : ");
  Serial.println(sensorValue);



  if (sensorValue >= 8) { // When Soil Moister is above 60 % Switch off the pump (LOW triger Relay)

    digitalWrite(Pump, HIGH);

  } else {

    digitalWrite(Pump, LOW);

  }

}
