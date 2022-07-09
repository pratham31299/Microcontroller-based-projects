
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


// GPIO pins

#define redledPin 10 // led's pins
#define greenledPin 9
#define motorPinA 8 // digital pin 8, L239D IC signal
#define motorPinB 7
#define IR_1 6  // IR proximity sensors
#define IR_2 5

// Variables

int IR_1State = 0;  // to store the IR sensor values
int IR_2State = 0;

int IR_Count = 0;  // to count the valus for IR sensore (Bidirectional)

void setup() {

  Serial.begin(9600); // at 9600 baud rate

  // Initialize the lcd
  lcd.init();
  lcd.init();
  lcd.backlight();

  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("AUTOMATIC");
  delay(3000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("RAILWAY GATE");
  lcd.setCursor(1, 1);
  lcd.print("CONTROL SYSYTEM");

  pinMode(redledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);

  delay(5000);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("READY");


}

void loop() {

  // read the state of the IR sensores:

  IR_1State = digitalRead(IR_1);
  IR_2State = digitalRead(IR_2);


  //*****************************CONTROL STRUCTURE********************************


  // check if :

  if (IR_1State == HIGH || IR_2State == HIGH) { // whenever train enter , both side -> CLOSE

    if (IR_Count == 0) {

      // turn OFF:
      digitalWrite(greenledPin, LOW);

      // Print a message to the LCD.
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("STOP");
      lcd.setCursor(15, 1); // indication (FC -> forward CLOSE)
      lcd.print("C");


      // turn ON:
      digitalWrite(redledPin, HIGH);
      digitalWrite(motorPinA, HIGH);
      delay(1500); // time, motor takes to close the Barrier Gate
      digitalWrite(motorPinA, LOW);
      delay(200);

      IR_Count = 1 ; // change varible value
      IR_1State = LOW; // change state
      IR_2State = LOW; // change state

    }
  }




  if (IR_Count == 1) { // whenever train exit,  IR_1 High, then IR_2 high -> OPEN

    if (IR_2State == HIGH) {

      // turn OFF:
      digitalWrite(redledPin, LOW);


      // Print a message to the LCD.
      lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("GO!");
      lcd.setCursor(14, 1); // indication
      lcd.print("FO"); // (Forward open -> IR_1 to IR_2)

      // turn ON:
      digitalWrite(greenledPin, HIGH);
      digitalWrite(motorPinB, HIGH);
      delay(1500); // time, motor takes to open the Barrier Gate
      digitalWrite(motorPinB, LOW);
      delay(200);

      IR_Count = 0 ; // change varible value

    }
  }


  if (IR_Count == 1) { // whenever train exit,  IR_2 High, then IR_1 high -> OPEN

    if (IR_1State == HIGH) {

      // turn OFF:
      digitalWrite(redledPin, LOW);


      // Print a message to the LCD.
      lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print("GO!");
      lcd.setCursor(14, 1); // indication
      lcd.print("BO");  // (Backward open -> IR_2 to IR_1)

      // turn ON:
      digitalWrite(greenledPin, HIGH);
      digitalWrite(motorPinB, HIGH);
      delay(1500); // time, motor takes to open the Barrier Gate
      digitalWrite(motorPinB, LOW);
      delay(200);

      IR_Count = 0 ; // change varible value

    }
  }
  
}
