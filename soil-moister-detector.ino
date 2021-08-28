int sensorPin = A7;    // select the input pin for the potentiometer
int led2 = 2;
int led3 = 3;
int led4 = 4;
int led5 = 5; // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {

  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  // read the value from the sensor:

  sensorValue = analogRead(sensorPin);// reads the value of the electrode (value between 0 and 1023)
  sensorValue = map(sensorValue, 0, 1023, 0, 15);     // scale it for use (value between 0 and 15)


  Serial.print(" Moister level : ");
  Serial.println(sensorValue);

  if (sensorValue >= 0) {

    digitalWrite(led2, HIGH);

  }

  if (sensorValue >= 5) {

    digitalWrite(led3, HIGH);
  }

  if (sensorValue >= 10) {

    digitalWrite(led4, HIGH);
  }

  if (sensorValue >= 15) {

    digitalWrite(led5, HIGH);

  } else {

    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

  }

}
