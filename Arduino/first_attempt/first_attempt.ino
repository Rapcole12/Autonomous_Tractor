/*==========================================================================
// Authors: Richard Martinez and Raphael Rodriguez
// Project: ECE 2804 Autonomous Tractor
// Description: Arduino script to control the motors using L298N motor driver
//==========================================================================
*/

// Program Output:
// Drive forward for 500 ms, wait 500 ms, drive backward 500 ms

// Definitions Arduino pins connected to input H Bridge
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int DELAY = 500; // ms

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
}

void loop()
{
  
}

void resetPins() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}