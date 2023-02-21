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

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
float toleranceAngle = 1.0;

// Definitions Arduino Pins
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int RX_PIN = 9;
int TX_PIN = 8;
int ENA = 10;
int ENB = 11;
int MAX_SPEED = 255; 
int SLOW_SPEED = 100;
int STOP_SPEED = 0;
int PUSHBUTTON_PIN = 13;

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
bool running = false;

void setup()
{
 
 SetPins();

  Serial.begin(9600);  // Serial Monitor
  BLESerial.begin(9600);  // Bluetooth Terminal
  Wire.begin(); // Gyroscope
  byte status = mpu.begin();
  
  // Zero out the gyro
  while (status != 0) {
    Serial.println("Could not connect to gyroscope");
  }

  BLESerial.println("About to zero gyroscope, DO NOT MOVE");
  Serial.println("About to zero gyroscope, DO NOT MOVE");
  delay(1000);
  mpu.calcOffsets(); // Calculate the zeros
  BLESerial.println("Ready to use!");
  Serial.println("Ready to use!");
}

void loop() {
  
  BLESetup();

  mpu.update();

  SetTimer();

  if (running) {
    KeepStraight();
  }
  else {
    motorA(STOP, STOP_SPEED);
    motorB(STOP, STOP_SPEED);
  }
}

void motorA(direction status, int speed) {
  if (status == STOP) {
    analogWrite(ENA, speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  else if (status == FORWARD) {
    // Turn Motor A Clockwise (Forward)
    analogWrite(ENA, speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (status == BACKWARD) {
    // Turn Motor A Counterclockwise (Backward)
    analogWrite(ENA, speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    return;
  }
  
}

void motorB(direction status, int speed) {
  if (status == STOP) {
    analogWrite(ENB, speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else if (status == FORWARD) {
    // Turn Motor B Counterclockwise (Forward)
    analogWrite(ENB, speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

  }
  else if (status == BACKWARD) {
    // Turn Motor B Clockwise (Backward)
    analogWrite(ENB, speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else {
    return;
  }
  
}

void SetPins(){
 // Set the output pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(PUSHBUTTON_PIN, INPUT);
}

void BLESetup(){
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
        running = true;
        BLESerial.print("Turned ON\n");
      }
      else if (message == "OFF") {
        running = false;
        BLESerial.print("Turned OFF\n");
      }
      else {
       message =  message + " is not a valid expression \n";
       BLESerial.print(message);
      }
    }

  }

}

void SetTimer(){

  if((millis()-timer)>10) {
	
    angleX = mpu.getAngleX();
    angleY = mpu.getAngleY();
    angleZ = mpu.getAngleZ();

    if(digitalRead(PUSHBUTTON_PIN) == HIGH) {
      running = !running;
      delay(250);
    }

	  timer = millis();  
  }

}

void KeepStraight(){

  if (angleZ < -toleranceAngle) {
    motorA(FORWARD, SLOW_SPEED);
    motorB(FORWARD, MAX_SPEED);
    Serial.println("Turning too far to the right");
  }
  else if (angleZ > toleranceAngle) {
    motorA(FORWARD, MAX_SPEED);
    motorB(FORWARD, SLOW_SPEED);
    Serial.println("Turning too far to the left");
  }
  else {
    motorA(FORWARD, MAX_SPEED);
    motorB(FORWARD, MAX_SPEED);
    Serial.println("Continue moving forward");
  }

}