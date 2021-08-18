
int redLed = 10;
int greenLed = 11;
int buzzer = 12;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 150;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Smoke Level : ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor >= sensorThres)
  {
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
    digitalWrite(greenLed, HIGH);
    delay(100);
    digitalWrite(greenLed, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(500);

  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, LOW);

  }
  delay(100);
}
