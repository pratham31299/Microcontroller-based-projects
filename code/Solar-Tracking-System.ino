/* Solar Tracking system

  July 22, 2022

*/

// GPIO pins

#define redledPin 10 // led's pins
#define greenledPin 9
#define motorPinA 8 // digital pin 8, L239D IC signal
#define motorPinB 7
#define switch1Pin 6 //digital pin 6,  limit switch pins
#define switch2Pin 5
#define ldr1Pin A0  //analog pin 0, LDR sensors
#define ldr2Pin A1

// Variables

int switch1State = 0;  // to store the limit switch values
int switch2State = 0;

int  ldr1Value = 0;  // variable to store the value coming from the LDR sensors
int  ldr2Value = 0;

int ldrDelta = 0; // to store difference between ldr values




void setup() {

  // Debugging console
  Serial.begin(9600); // at 9600 baud rate

  // initialize GPIO pins
  pinMode(redledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

  pinMode(switch1Pin, INPUT_PULLUP);  // initially HIGH
  pinMode(switch2Pin, INPUT_PULLUP);

  //
  Serial.println("Solar Tracker Begin");
}

void loop() {

  // read the state of the limit switches:

  switch1State = digitalRead(switch1Pin);
  switch2State = digitalRead(switch2Pin);


  // read the value from the sensor:
  ldr1Value = analogRead(ldr1Pin);
  ldr2Value = analogRead(ldr2Pin);

  ldrDelta = ldr1Value - ldr2Value ;  // getting difference between values

  Serial.print("--------------------------------LDR Delta ");
  Serial.println(ldrDelta);



  //*********************Control Structure******************


  if (ldrDelta > 200) { // 200 threshold  difference (ldr1 > ldr2 ), move solar panel to east,

    // turn OFF:
    digitalWrite(greenledPin, LOW);

    // turn ON:
    digitalWrite(redledPin, HIGH);

    digitalWrite(motorPinA, HIGH);
    delay(100); // motor delay, per step
    digitalWrite(motorPinA, LOW);
    delay(50);
    digitalWrite(motorPinA, HIGH);

    Serial.println("--------------------------------Moving to east");

  }



  if (ldrDelta < - 200) {  // -200 threshold difference (ldr1 < ldr2 ), move solar panel to west

    // turn OFF:
    digitalWrite(greenledPin, LOW);

    // turn ON:
    digitalWrite(redledPin, HIGH);

    digitalWrite(motorPinB, HIGH);
    delay(100); // motor delay, per step
    digitalWrite(motorPinB, LOW);
    delay(50);
    digitalWrite(motorPinB, HIGH);

    Serial.println("--------------------------------Moving to weast");

  }



  if (switch1State == LOW) {  // limit switch 1 pressed

    // turn OFF:
    digitalWrite(greenledPin, LOW);

    Serial.println("--------------------------------Limit switch 1 pressed");
    

    while (switch2State == HIGH)  // while stop limit switch is not pressed
    {
      // turn ON:
      digitalWrite(motorPinB, HIGH); // turn solar panel to reset position (east)
      digitalWrite(redledPin, HIGH);
      // check
      switch2State = digitalRead(switch2Pin);

    }


    // turn OFF:

    digitalWrite(motorPinA, LOW);// stop !
    digitalWrite(motorPinB, LOW);


  }



  if (switch2State == LOW) { // limit switch 2 pressed

    // turn OFF:

    digitalWrite(motorPinA, LOW);// stop !
    digitalWrite(motorPinB, LOW);

    digitalWrite(greenledPin, LOW);

    // turn ON:
    digitalWrite(redledPin, HIGH);
    delay(500);

    Serial.println("--------------------------------Limit switch 2 pressed");
  }



  if (ldrDelta < 200 && ldrDelta > -200 && switch1State == HIGH && switch2State == HIGH ) {  // under threshold  values

    // turn OFF:
    digitalWrite(redledPin, LOW);

    digitalWrite(motorPinA, LOW);// stop !
    digitalWrite(motorPinB, LOW);


    // turn ON:
    digitalWrite(greenledPin, HIGH);

    Serial.println("-------------------------------Stable");


  }



  // Debug data stream

  Serial.print("LDR 1 : ");
  Serial.print(ldr1Value);
  Serial.print(" LDR 2 : ");
  Serial.print(ldr2Value);
  Serial.println(" ");

}
