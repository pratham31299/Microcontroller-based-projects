/* Temperature Controlled Fan using Arduino

*/

//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// OUTPUT GPIO pins

#define Fan 9 // fan attached to GPIO pin 9 (PWM)
#define led2 2
#define led3 3
#define led4 4

// INPUT GPIO pin

#define Temp_sensorPin A0 // LM35 is connected to this PIN


// Variables
float  temp ; // varible for sensor
int val ; // to store the rpm data for fan
int rpm = 0 ;



void setup() {


  Serial.begin(9600); // at 9600 baud rate

  // Initialize the lcd
  lcd.init();
  lcd.init();

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Controlled-Fan");

  //Defining Led pins as output

  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);



}

void loop() {

  temp = analogRead(Temp_sensorPin ); // Read Pin A0 for temperature

  // Convert that ADC Data into voltage (5.0 / 1024.0),  Convert the voltage into temperature (* 100)
  temp = temp * 0.48828122 ;// multiply temp redings by constant factor to get readings in celcius


  val = temp ;    // reads the value of the temperature
  val = map(val, 0, 45, 0, 255);     // scale it for use with fan (value between 0 and 255), max speed at 45*C


  analogWrite(Fan, val);  // sets the fan speed according to the scaled value


  rpm = val * 9.25; // constant for rpm



  // for debugging

  Serial.print(" temperature ");
  Serial.print(temp);
  Serial.print(" *C");

  Serial.print(" , FanSpeed  ");
  Serial.print(val);
  Serial.println(" PWM");

  // LCD show

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature ");
  lcd.setCursor(12, 0);
  lcd.print(temp);
  lcd.setCursor(14, 0);
  lcd.print("*C");
  lcd.setCursor(0, 1);
  lcd.print("RPM :");
  lcd.setCursor(6, 1);
  lcd.print(rpm);



  // Led control structure

  if (temp > 25) {

    digitalWrite(led2, HIGH);
    delay(500);

  }
  if (temp > 35) {

    digitalWrite(led3, HIGH);
    delay(500);

  }
  if (temp > 44) {

    digitalWrite(led4, HIGH);
    delay(500);

  } else {

    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}
