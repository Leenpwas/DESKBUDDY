/*
  6-DOF Robotic Arm – Servo Test Code
  Controller : ESP32
  Servos     : ST3215 Digital Servos (25kg·cm)
  PWM Freq   : 50 Hz (standard for hobby servos)
  Note       : Servos require external 6V–7.4V supply.
*/

#include <ESP32Servo.h>

// Servo objects
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristPitchServo;
Servo wristRollServo;
Servo gripperServo;

// PWM pins (change according to your wiring)
#define BASE_PIN         13
#define SHOULDER_PIN     12
#define ELBOW_PIN        14
#define WRIST_PITCH_PIN  27
#define WRIST_ROLL_PIN   26
#define GRIPPER_PIN       25

// Motion limits for safety (adjust based on your mechanical design)
int baseMin = 20,  baseMax = 160;
int shoulderMin = 10, shoulderMax = 160;
int elbowMin = 10, elbowMax = 150;
int wristPitchMin = 0, wristPitchMax = 180;
int wristRollMin = 0, wristRollMax = 180;
int gripperOpen = 80, gripperClose = 140;

// Smooth movement helper
void moveServo(Servo &servo, int start, int end, int delayMs = 10) {
  if (start < end) {
    for (int pos = start; pos <= end; pos++) {
      servo.write(pos);
      delay(delayMs);
    }
  } else {
    for (int pos = start; pos >= end; pos--) {
      servo.write(pos);
      delay(delayMs);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("6-DOF Robotic Arm Test Starting...");

  // Attach all servos
  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  elbowServo.attach(ELBOW_PIN);
  wristPitchServo.attach(WRIST_PITCH_PIN);
  wristRollServo.attach(WRIST_ROLL_PIN);
  gripperServo.attach(GRIPPER_PIN);

  // Move to a safe home position
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(100);
  wristPitchServo.write(90);
  wristRollServo.write(90);
  gripperServo.write(gripperOpen);

  Serial.println("Servos initialized.");
  delay(2000);
}

void loop() {
  Serial.println("Running joint sweep test...");

  // Base rotation test
  moveServo(baseServo, 90, baseMax);
  moveServo(baseServo, baseMax, baseMin);
  moveServo(baseServo, baseMin, 90);

  // Shoulder test
  moveServo(shoulderServo, 90, shoulderMax);
  moveServo(shoulderServo, shoulderMax, shoulderMin);
  moveServo(shoulderServo, shoulderMin, 90);

  // Elbow test
  moveServo(elbowServo, 100, elbowMax);
  moveServo(elbowServo, elbowMax, elbowMin);
  moveServo(elbowServo, elbowMin, 100);

  // Wrist pitch test
  moveServo(wristPitchServo, 90, wristPitchMax);
  moveServo(wristPitchServo, wristPitchMax, wristPitchMin);
  moveServo(wristPitchServo, wristPitchMin, 90);

  // Wrist roll test
  moveServo(wristRollServo, 90, wristRollMax);
  moveServo(wristRollServo, wristRollMax, wristRollMin);
  moveServo(wristRollServo, wristRollMin, 90);

  // Gripper open/close test
  Serial.println("Testing gripper...");
  moveServo(gripperServo, gripperOpen, gripperClose, 5);
  delay(300);
  moveServo(gripperServo, gripperClose, gripperOpen, 5);
  delay(300);

  Serial.println("Test cycle complete.\n");
  delay(1000);
}
