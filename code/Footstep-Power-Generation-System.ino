
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


// GPIO pins

float piezo_analog = A0; // voltage divider on analog pin A0 (piezo)
float bat_analog = A1; // voltage divider on analog pin A1 (battery)
const int step_led = 13 ; // led indicator for footstep

//Variables

float P_value = 0; // to store analog readings
float B_value = 0;

float P_voltage = 0; // to store voltage raedings
float B_voltage = 0;

float R1 = 100000.0 ; // R1 (100k)
float R2 = 10000.0  ;// R2 (10k)

int step_count = 0; // to count footstep




void setup() {

  // initialize the lcd

  lcd.init();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Initializing....");

  Serial.begin(9600);
  Serial.println(" FootStep Power Generation system begain !");

  pinMode(piezo_analog, INPUT);
  pinMode(bat_analog, INPUT);

  pinMode(step_led, OUTPUT);

  // Print a message to the LCD.
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Foot Step Power ");
  lcd.setCursor(3, 1);
  lcd.print("Generator");
  delay(5000);

  lcd.setCursor(0, 0);
  lcd.print("Plug the Piezo  ");
  lcd.setCursor(0, 1);
  lcd.print("plate & Battery! ");
  delay(4000);
  lcd.clear();

}

void loop() {

  // analog read to get data form input

  P_value = analogRead(piezo_analog); //Piezo plate
  B_value = analogRead(bat_analog); // Battery pack


  // Calculation of voltage

  P_voltage = P_value * (5.0 / 1023) * ((R1 + R2) / R2); // Calculation of voltage for Piezo plate

  B_voltage = B_value * (4.0 / 1023) * ((R1 + R2) / R2); // Calculation of voltage for Battery


 /* P_voltage =   P_voltage * 20 ; // arbitrary value for piezo's voltage */


  if ( P_voltage > 0.50) { // minimum  voltage which can be detecteds

    step_count++; // for footstep incriment by 1
    digitalWrite(step_led, HIGH);
    delay(200);
  }
  digitalWrite(step_led, LOW); // step led always low


  if (B_voltage < 4.0 ) { // minimum battery discharge voltage Alert !!

    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Battery low !   ");
    Serial.println(" Battery Low !!!!!!!!!!!!!!!!!!!!!!!!!   ");
    delay(2000);
  }




  //Print data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Steps : ");
  lcd.setCursor(9, 0);
  lcd.print(step_count);
  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.setCursor(2, 1);
  lcd.print(P_voltage);
  lcd.setCursor(8, 1);
  lcd.print("BV:");
  lcd.setCursor(12, 1);
  lcd.print(B_voltage);


  // debugging values
  Serial.print("Piezo Analog read  : ");
  Serial.print(P_value);
  Serial.print(" Piezo Voltage read : ");
  Serial.print(P_voltage);
  Serial.print(" Footsetps : ");
  Serial.print(step_count);
  Serial.print(" Battery Analog read  : ");
  Serial.print(B_value);
  Serial.print(" Battery Voltage read : ");
  Serial.println(B_voltage);
  delay(200);
}
