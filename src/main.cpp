/**********************************************************************
  Filename    : Servo Sweep
  Description : Control the servo motor for sweeping
  Auther      : www.freenove.com
  Modification: 2024/06/21
**********************************************************************/
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

int posVal = 0;    // variable to store the servo position
int servoPin = 15; // Servo motor pin

int xPin = 25;

void setup() {
  pinMode(xPin, INPUT_PULLUP);
  myservo.setPeriodHertz(50);           // standard 50 hz servo
  myservo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
}
void loop() {
  int xVal = analogRead(xPin);
  xVal = map(xVal,0, 4095, 0, 180);

  myservo.write(xVal);
  delay(15);
}
