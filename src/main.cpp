/**********************************************************************
  Filename    : Automacao_automatica
  Description : controle de casa inteligente
  Auther      : Eng.Wilhan Almeida
  Criado: 15/05/2026
**********************************************************************/
#include <ESP32Servo.h>

int motorPortas[] = {14,27,26,25};

int joystick = 34;

void moveSteps(bool dir, int steps, byte ms);
void moveOneStep(bool dir);
void moveAround(bool dir, int turns, byte ms);
void moveAngle(bool dir, int angle, byte ms);

void setup(){
  for(int i = 0; i<4; i++){
    pinMode(motorPortas[i], OUTPUT);
  }
  pinMode(joystick, INPUT_PULLUP);
}

void loop(){
   int xVal = analogRead(joystick);
   
   if(xVal > 3000){
    moveSteps(true, 32 * 64, 3);
   }
   if(xVal < 1200){
    moveSteps(false, 32 * 64, 3);
   }
}


//Suggestion: the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms,3,20));        // Control the speed
  }
}

void moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) {  // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else {      // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(motorPortas[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

void moveAround(bool dir, int turns, byte ms){
  for(int i=0;i<turns;i++)
    moveSteps(dir,32*64,ms);
}
void moveAngle(bool dir, int angle, byte ms){
  moveSteps(dir,(angle*32*64/360),ms);
}

// Servo myservo;  // create servo object to control a servo

// int posVal = 0;    // variable to store the servo position
// int servoPin = 15; // Servo motor pin

// int xPin = 25;

// void setup() {
//   pinMode(xPin, INPUT_PULLUP);
//   myservo.setPeriodHertz(50);           // standard 50 hz servo
//   myservo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
// }
// void loop() {
//   int xVal = analogRead(xPin);
//   xVal = map(xVal,0, 4095, 0, 180);

//   myservo.write(xVal);
//   delay(15);
// }
