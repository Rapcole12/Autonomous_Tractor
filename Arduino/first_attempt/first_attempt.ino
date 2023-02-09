/*==========================================================================
// Authors: Richard Martinez and Raphael Rodriguez
// Project: ECE 2804 Autonomous Tractor
// Description: Arduino script to control the motors using L298N motor driver
//==========================================================================
*/

// Program Output:
// Toggle drive forward and stop with button press

// Definitions Arduino pins connected to input H Bridge
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int ENA = 9;
int ENB = 10;
int DELAY = 500; // ms
int PUSHBUTTON_PIN = 3;
int PUSHBUTTON = 0;

// Add motor status functions
int FORWARD = 1;
int STOP = 0;
int BACKWARD = -1;

// Current moving direction
int DIRECTION = STOP;

void setup()
{
    // Set the output pins
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    resetPins();
}

void loop()
{
  analogWrite(ENA, 50);  // ONLY between 0, 255 but recommeneded 50 to 255
  analogWrite(ENB, 255);
  // Drive forward when button is pressed, otherwise stop
  PUSHBUTTON = digitalRead(PUSHBUTTON_PIN); // Grab HIGH or LOW from button

  if (PUSHBUTTON == HIGH) {
    DIRECTION = !DIRECTION;  // Toggle 0 to 1 or 1 to 0;
    motorA(DIRECTION);
    motorB(DIRECTION);
  }
}

void motorA(int status) {
  if (status == STOP) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  else if (status == FORWARD) {
    // Turn Motor A Clockwise (Forward)
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (status == BACKWARD) {
    // Turn Motor A Counterclockwise (Backward)
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    return;
  }
}

void motorB(int status) {
  if (status == STOP) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else if (status == FORWARD) {
    // Turn Motor B Counterclockwise (Forward)
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if (status == BACKWARD) {
    // Turn Motor B Clockwise (Backward)
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else {
    return;
  }
}

void resetPins() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}