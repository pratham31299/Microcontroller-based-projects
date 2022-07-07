
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

float piezo_analog = A0; // voltage divider on analog pin A0 (piezo)
float vout = 0.0;
float vin = 0.0;
int value = 0;

float bat_analog = A1; // voltage divider on analog pin A1 (battery)
float Bvout = 0.0;
float Bvin = 0.0;
int Bvalue = 0;

float R1 = 100000.0 ; // R1 (100k)
float R2 = 10000.0  ;// R2 (10k)

int step_count = 0; // to count footstep
const int step_led = 13 ; // led indicator



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

  // Calculation of voltage for Piezo plate

  value = analogRead(piezo_analog); // analog read to get data form Input ( 0 v = 0 , 5 v = 1023)

  vout = (value * 5.0 ) / 1024.0 ; // Converting it into voltage Respectively
  vin = vout / (R2 / ( R1 + R2)); //voltage divider formula
    

  // Calculation of voltage for Battery

  Bvalue = analogRead(bat_analog); // analog read to get data form Input ( 0 v = 0 , 5 v = 1023)

  Bvout = (Bvalue * 5.0 ) / 1024.0 ; // Converting it into voltage Respectively
  Bvin = Bvout / (R2 / ( R1 + R2)); //voltage divider formula
    
  

  if ( vin > 0.50) { // minimum  voltage which can be detecteds

    step_count++; // for footstep incriment by 1
    digitalWrite(step_led, HIGH);
    delay(200);
  }
  digitalWrite(step_led, LOW); // step led always low


  if (Bvin < 4.0 ) { // minimum battery discharge voltage Alert !!

    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Battery low !   ");
    Serial.println(" Battery Low !!!!!!!!!!!!!!!!!!!!!!!!!   ");
    delay(2000);
  }

 // vin = vin*8 ;       // arbitrary value for piezo's voltage

  //Print data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Steps : ");
  lcd.setCursor(9, 0);
  lcd.print(step_count);
  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.setCursor(2, 1);
  lcd.print(vin);
  lcd.setCursor(8, 1);
  lcd.print("BV:");
  lcd.setCursor(12, 1);
  lcd.print(Bvin);


  // debugging values
  Serial.print("Piezo Analog read  : ");
  Serial.print(value);
  Serial.print(" Piezo Voltage read : ");
  Serial.print(vin);
  Serial.print(" Footsetps : ");
  Serial.print(step_count);
  Serial.print(" Battery Analog read  : ");
  Serial.print(Bvalue);
  Serial.print(" Battery Voltage read : ");
  Serial.println(Bvin);
  delay(200);
}
