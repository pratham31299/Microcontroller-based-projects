
int redLed = 2;
int greenLed = 3;
int buzzer = 4;
int smoke = A7;
// Your threshold value
int sensorThres = 380;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smoke, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smoke);

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
