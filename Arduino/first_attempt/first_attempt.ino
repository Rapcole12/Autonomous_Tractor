/*==========================================================================
// Authors: Richard Martinez and Raphael Rodriguez
// Project: ECE 2804 Autonomous Tractor
// Description: Arduino script to control the motors using L298N motor driver
//==========================================================================
*/

// Program Output:
// Drive forward only when button is pressed

// Definitions Arduino pins connected to input H Bridge
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int DELAY = 500; // ms
int PUSHBUTTON_PIN = 3;
int PUSHBUTTON = 0;

// Add motor status functions
int FORWARD = 1;
int STOP = 0;
int BACKWARD = -1;

void setup()
{
    // Set the output pins
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    resetPins();

    // NOTE: The white turning wheel is the "front" of the tractor
    // Therefore, motor A is the left wheel, motor B is the right wheel

    // NOTE: "Clockwise" is from the point of view of the center of the tractor
    // That means that "clockwise" is forward for A, but backwards for B

    /*
    // Turn Motor A Clockwise (Forward)
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Turn Motor B Counterclockwise (Forward)
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    // Delay
    delay(DELAY);  // Drive forward
    resetPins();
    delay(DELAY);  // Stop and wait

    // Turn Motor A Counterclockwise (Backward)
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    // Turn Motor B Clockwise (Backward)
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // Delay, then quit
    delay(DELAY);  // Drive backward
    resetPins();
    exit(0);
    */
}

void loop()
{
  // Drive forward when button is pressed, otherwise stop
  PUSHBUTTON = digitalRead(PUSHBUTTON_PIN); // Grab HIGH or LOW from button
  if (PUSHBUTTON == HIGH) {
    motorA(FORWARD);
    motorB(FORWARD);
  }
  else {
    motorA(STOP);
    motorB(STOP);
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