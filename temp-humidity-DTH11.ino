

// REQUIRES the following Arduino libraries:

// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

int lowT = 3;
int highT = 4; // above 35 deg celcius

int lowH = 5;
int highH = 6; // above 80 %



DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  Serial.println(F("DHT11 test!"));

  dht.begin();

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


  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  if (t > 0) {

    digitalWrite(lowT, HIGH);

  }

  if (t >= 35) {

    digitalWrite(highT, HIGH);

  }


  if (h > 0) {

    digitalWrite(lowH, HIGH);

  }

  if (h >= 80) {

    digitalWrite(highH, HIGH);

  } else {

    digitalWrite(lowT, LOW);
    digitalWrite(lowH, LOW);
    digitalWrite(highH, LOW);
    digitalWrite(highT, LOW);

  }

}
