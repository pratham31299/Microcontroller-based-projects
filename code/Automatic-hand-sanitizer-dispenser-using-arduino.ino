#include <Servo.h> // servo library

#define trigPin 3 // digital GPIO
#define echoPin 2

long duration;
int distance, Meas_distance;

Servo my_servo; // servo instance



int Cal_distance() {  // function to calculate distance

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // formula

  return distance ; // return distance value

}


void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  my_servo.attach(9); // digital pin 9 (PWM)
  my_servo.write(0); // initial position

}


void loop() {

  Meas_distance =  Cal_distance(); // call function


  // Controle Structure------------------

  if ( Meas_distance < 10) { // 10 cm

    Serial.println("HOLD ON");
    my_servo.write(95);
    delay(2000);
    my_servo.write(0);

  } else {
    Serial.print(Meas_distance);
    Serial.println(" cm");
  }

  delay(1000); // a bit of delay
}
