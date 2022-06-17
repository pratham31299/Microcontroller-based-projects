#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// REQUIRES the following Arduino libraries:

// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// GPIO's

#define lowT 3
#define highT 4 // above 35 deg celcius
#define lowH 5
#define highH 6 // above 80 %

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

DHT dht(DHTPIN, DHTTYPE); // DHT sensor instence

void setup() {

  Serial.begin(9600);
  dht.begin();
  lcd.init();                      // initialize the lcd
  lcd.init();

  Serial.println(F("DHT11 begain !"));

  // Print a message to the LCD.
  lcd.backlight();
  // Print message on LCD

  lcd.setCursor(0, 0);
  lcd.print("Initializing....");
  delay(2000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Temp/Humidity");
  lcd.setCursor(4, 1);
  lcd.print("Detector");
  delay(2000);
  lcd.clear();


  // GPIO pins as OUTPUT

  pinMode(lowT, OUTPUT);
  pinMode(highT, OUTPUT);
  pinMode(lowH, OUTPUT);
  pinMode(highH, OUTPUT);


}

void loop() {
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Send data to debugging console

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  // Send data to LCD

  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(13, 0);
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Humidity % :");
  lcd.setCursor(13, 1);
  lcd.print(h);


  // Control structurefor  OUTPUT Led's-----------------------

  if (t > 0) {
    digitalWrite(lowT, HIGH);
    delay(200);
  }
  if (t >= 35) {
    digitalWrite(highT, HIGH);
    delay(200);
  }
  if (h > 0) {
    digitalWrite(lowH, HIGH);
    delay(200);
  }
  if (h >= 80) {
    digitalWrite(highH, HIGH);
    delay(200);

  } else {
    digitalWrite(lowT, LOW);
    digitalWrite(lowH, LOW);
    digitalWrite(highH, LOW);
    digitalWrite(highT, LOW);
  }

}
