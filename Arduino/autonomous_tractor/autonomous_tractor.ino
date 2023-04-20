/*
==========================================================================
Authors: Richard Martinez and Raphael Rodriguez
Project: ECE 2804 Autonomous Tractor
Description: Arduino script implementing a self-driving tractor
Included Features: L298N Motor Driver, HM-10 BLE Module, MPU-9250 Gyroscope
==========================================================================
*/

// Includes for BLE
#include "Arduino.h"
#include <SoftwareSerial.h>

// Includes for Gyroscope
#include "Wire.h"
#include <MPU6050_light.h>

// Init Gyroscope
MPU6050 mpu(Wire);
unsigned long timer = 0;
unsigned long last_time = 0;
float angleX = 0;
float angleY = 0;
float angleZ = 0;
float toleranceAngle = 1.0;
int MAX_SPEED = 80; 
int SLOW_SPEED = 20;  // CHANGED FROM 100 to 50
int STOP_SPEED = 0;
long duration; 
int distance; 
int IR_THRESHOLD = 100;
int bearing = 0;

// Definitions Arduino Pins
int EMERGENCY_STOP = 2;
int TRIG = 3;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int RX_PIN = 9;
int TX_PIN = 8;
int ENA = 10;
int ENB = 11;
int PUSHBUTTON_PIN = 13;
int IR_DIODE = A0;

// Init BLE
SoftwareSerial BLESerial(RX_PIN, TX_PIN); //call the constructor for Software Serial

// Enum to control direction of the tractor
enum direction {
    STOP,
    FORWARD,
    BACKWARD
};

// Current moving direction
direction DIRECTION = STOP;

String temp_message = ""; // this will extract each character and concatenate previous characters from the phone
String message = ""; //this will be the actual message that will determine wehther the motor turns on or off

// Is the tractor running?
bool running = false;

int zeroDetect = 0;
int blackTapeDetect = 0;
int counter = 0;
int numBlackTapes = 0;

void setup()
{
  // Init Pins as INPUT or OUTPUT
  SetPins();

  // Init Serial Monitor, BLE, and Gyro
  Serial.begin(9600);  // Serial Monitor
  BLESerial.begin(9600);  // Bluetooth Terminal
  Wire.begin(); // Gyroscope
  byte status = mpu.begin();
  
  // Stop if gyro can't connect
  while (status != 0) {
    Serial.println("Could not connect to gyroscope");
  }

  // Zero out the gyro
  BLESerial.println("About to zero gyroscope, DO NOT MOVE");
  Serial.println("About to zero gyroscope, DO NOT MOVE");
  delay(1000);
  mpu.calcOffsets(); // Calculate the zeros
  BLESerial.println("Ready to use!");
  Serial.println("Ready to use!");
}

void loop() {
  // Parse and Handle BLE
  BLESetup();

  // Update gyro data
  mpu.update();

  // Grab gyro data and check pushbutton every 10 ms
  SetTimer();

 // Drive Straight when Running
    if (running) {
     KeepStraight();
    }
    else {
      motorA(STOP, STOP_SPEED);
      motorB(STOP, STOP_SPEED);
    } 

    digitalWrite(TRIG,LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10); 
    digitalWrite(TRIG,LOW);

    int eStop = digitalRead(EMERGENCY_STOP);
    bool constantOnes = detectConstantOnes(eStop);
    //Serial.println(constantOnes);
    //Serial.println(running);

    if (constantOnes) {
      motorA(STOP, 0);
      motorB(STOP, 0);
      //Serial.println("EMERGENCY STOP");
    }

    blackTapeDetect = analogRead(IR_DIODE);
    //Serial.println(blackTapeDetect);
    if (blackTapeDetect < IR_THRESHOLD && counter == 0) {
      numBlackTapes++;
      BLESerial.print("BLACK TAPE\n");
      if (numBlackTapes == 3 || numBlackTapes == 4) {
        bearing -= 90;
      }
      else {
        bearing += 90;
      }
      if (bearing >= 360) {
        bearing = bearing - 360;
      }
      counter++;
    }

    if (counter > 0) {
      counter++;
      if (counter == 300) {
        counter = 0;
      }
    }

    //Serial.println(counter);
    //Serial.println(bearing);
}

void motorA(direction status, int speed) {
  if (status == STOP) {
    // Stop Moving
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
    // Stop Moving
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
  pinMode(TRIG, OUTPUT);
  pinMode(EMERGENCY_STOP, INPUT);
  pinMode(IR_DIODE, INPUT);
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
  if (angleZ < -toleranceAngle + bearing) {
    // Turning too far to the right
    motorB(FORWARD, MAX_SPEED);

    if (counter == 0) {  // Not Turning
      motorA(FORWARD, SLOW_SPEED);
    }
    else {
      motorA(STOP, 0);
    }
    //Serial.println("Turning too far to the right");
  }
  else if (angleZ > toleranceAngle + bearing) {
    // Turning too far to the left
    motorA(FORWARD, MAX_SPEED);

    if (counter == 0) {  // Not Turning
      motorB(FORWARD, SLOW_SPEED);
    }
    else {
      motorB(STOP, 0);
    }
    //Serial.println("Turning too far to the left");
  }
  else {
    // Keep moving forward
    motorA(FORWARD, MAX_SPEED);
    motorB(FORWARD, MAX_SPEED);
    //Serial.println("Continue moving forward");
  }
}

bool detectConstantOnes(int i) {
  zeroDetect++;
  if (i == 0) {
    zeroDetect = 0;
  }

  if (zeroDetect > 15) {
    return true;
  }
  return false;
}