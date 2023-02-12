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

SoftwareSerial BLESerial(RX_PIN, TX_PIN);

enum direction {
    STOP,
    FORWARD,
    BACKWARD
};

// Current moving direction
direction DIRECTION = STOP;

String messageBuffer = "";
String message = "";

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

void loop()
{
  while (BLESerial.available() > 0) {
    char next = (char) BLESerial.read();
    messageBuffer += next;
    if (next == ';') {
      message = messageBuffer;
      messageBuffer = "";
      Serial.print(message);
      message.trim();
      if (message == "on;") {
        motorA(FORWARD);
        motorB(FORWARD);
      }
      else if (message == "off;") {
        motorA(STOP);
        motorB(STOP);
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