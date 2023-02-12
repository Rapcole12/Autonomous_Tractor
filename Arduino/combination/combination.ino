/*==========================================================================
// Authors: Richard Martinez and Raphael Rodriguez
// Project: ECE 2804 Autonomous Tractor
// Description: Arduino script to control the motors using L298N motor driver
//==========================================================================
*/

// Program Output:
// Toggle drive forward and stop with bluetooth command

#include "Arduino.h"
#include <SoftwareSerial.h>

// Definitions Arduino Pins
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int RX_PIN = 9;
int TX_PIN = 8;

SoftwareSerial BLESerial(RX_PIN, TX_PIN); //call the constructor for Software Serial

enum direction {
    STOP,
    FORWARD,
    BACKWARD
};

// Current moving direction
direction DIRECTION = STOP;

String temp_message = ""; // this will extract each character and concatenate previous characters from the phone
String message = ""; //this will be the actual message that will determine wehther the motor turns on or off

void setup()
{
  // Set the output pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(9600);
  BLESerial.begin(9600);
}

void loop(){

  //This while loop ensures that we are connected to the BLESerial
  while (BLESerial.available() > 0) {
      
    char next_char = (char) BLESerial.read(); //reads each character because the .read function can read one character at a time
    temp_message += next_char; //concatenates all characters put in terminal from phone

    if (next_char == '\n') {

      message = temp_message;
      temp_message = ""; //resets temp_message in terminal
      Serial.print(message);
      message.trim(); // takes away the new line character
      message.toUpperCase(); //ensures that message is case-insensitive

      if (message == "ON") {
        motorA(FORWARD);
        motorB(FORWARD);
      }

      else if (message == "OFF") {
        motorA(STOP);
        motorB(STOP);
      }

      else {
       message =  message + " is not a valid expression \n";
       BLESerial.print(message);
      }

    }

  }

}

void motorA(direction status) {
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

void motorB(direction status) {
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