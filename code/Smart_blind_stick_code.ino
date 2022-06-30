/*
  July 1,  2022

*/

#include <DFRobot_SIM808.h>
#include <SoftwareSerial.h>

#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX, PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//DFRobot_SIM808 sim808(&Serial);

//SMS receiving phone number, need to change
#define PHONE_NUMBER "85XXXXXXXX"

char MESSAGE[300];
char lat[12];
char lon[12];


const int trigPin  = 9;
const int echoPin = 8;

const int  buzzer = 12 ;
const int buttonPin = 13 ;

//Variables

long duration;
int distance;
int Meas_distance;

int buttonState;  // variable for reading the pushbutton status






void gps_location() { // function to get GPS data


  //************** Get GPS data *******************

  while (!sim808.getGPS()) { // enable GPS, until loop/wait

  }

  Serial.println("Getting GPS data..........");
  Serial.print("latitude :");
  Serial.println(sim808.GPSdata.lat, 6);
  Serial.print("longitude :");
  Serial.println(sim808.GPSdata.lon, 6);

  // send link
  Serial.print("http://maps.google.com/maps?q=loc:");
  Serial.print(sim808.GPSdata.lat, 6);
  Serial.print(",");
  Serial.println(sim808.GPSdata.lon, 6);

  // Prepare it to send as message

  float la = sim808.GPSdata.lat;
  float lo = sim808.GPSdata.lon;

  dtostrf(la, 6, 6, lat); //put float value of la into char array of lat. 6 = number of digits before decimal sign. 2 = number of digits after the decimal sign.
  dtostrf(lo, 6, 6, lon); //put float value of lo into char array of lon

  sprintf(MESSAGE, "Smart Blind Stick \nEmergency ! Location \nLatitude : %s\nLongitude : %s\nhttp://maps.google.com/maps?q=%s,%s\n", lat, lon, lat, lon);

  Serial.println("Message:");  // final message contents
  Serial.println(MESSAGE );

  //************* Turn off the GPS power ************
  // sim808.detachGPS();



  //**********************Send SMS**************************
  Serial.println("Start to send message ...");

  //******** define phone number and text **********
  sim808.sendSMS(PHONE_NUMBER, MESSAGE);

}



int Cal_distance() {  // function to calculate distance

  //Initial
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //pulse

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // formula

  return distance ; // return distance value

}




void setup() {

  mySerial.begin(9600);  // SIM808 Serial
  Serial.begin(9600);  //Debug Console


  //******** Initialize sim808 module *************
  while (!sim808.init()) {
    delay(1000);
    Serial.print("Sim808 init error\r\n");
  }
  delay(3000);
  Serial.println("Sim808 init success");



  //************* Turn on the GPS power************
  if ( sim808.attachGPS())
    Serial.println("Open the GPS power success");
  else
    Serial.println("Open the GPS power failure");



  Serial.println("Waiting for Signal.........."); // GPS conneting to satellite



  while (!sim808.getGPS()) { // enable GPS, until loop/wait

  }



  // *********** Initialize digital GPIO pins**********
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP); // button pin's as input, HIGH

  Serial.println("---------------Smart blind stick begin---------------");



}

void loop() {


  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  Meas_distance =  Cal_distance(); // call distance function


  // Controle Structure-----------------------------------------------------------


  // Blind stick Obstacle detection

  if ( Meas_distance < 100) { // 100 cm,

    Serial.println("Obstacle ! Alert");

    digitalWrite(buzzer, HIGH); // Obstacle alert at 100cm
    delay(2000);
    digitalWrite(buzzer, LOW);

  } else {
    digitalWrite(buzzer, LOW);
  }


  // Check if the emergency push button is pressed
  if (buttonState == LOW) {

    Serial.println("");
    Serial.println("Emergency Button pressed !");
    Serial.println("");

    gps_location(); // cal function


  } else { // print distance

    Serial.print("Distance: ");
    Serial.print(Meas_distance);
    Serial.println(" cm");
  }


  delay(1000);  // wait for a second
}
