/*
   6-DOF Robotic Arm — RECORD & PLAY SYSTEM
   -----------------------------------------
   Features:
   - Record up to N poses (joint angles of all 6 servos)
   - Playback recorded motion with smooth interpolation
   - Controlled via Serial commands:
       R → Start Recording
       S → Stop Recording
       P → Play
*/

#include <ESP32Servo.h>

// ------- Servo Setup -------
Servo baseServo, shoulderServo, elbowServo, wristPitchServo, wristRollServo, gripperServo;

#define BASE_PIN         13
#define SHOULDER_PIN     12
#define ELBOW_PIN        14
#define WRIST_PITCH_PIN  27
#define WRIST_ROLL_PIN   26
#define GRIPPER_PIN       25

// ------- Recording System -------
#define MAX_STEPS 300          // Maximum recorded positions
int recordBase[MAX_STEPS];
int recordShoulder[MAX_STEPS];
int recordElbow[MAX_STEPS];
int recordWristPitch[MAX_STEPS];
int recordWristRoll[MAX_STEPS];
int recordGripper[MAX_STEPS];

int recordIndex = 0;
bool isRecording = false;

// Sampling delay (ms)
int sampleInterval = 150;

// ------- Smooth Movement Helper -------
void smoothMove(Servo &servo, int start, int end, int delayMs = 5) {
  if (start == end) return;

  int step = (start < end) ? 1 : -1;
  for (int pos = start; pos != end; pos += step) {
    servo.write(pos);
    delay(delayMs);
  }
  servo.write(end);
}

// ------- Capture Current Pose -------
void capturePose() {
  recordBase[recordIndex]        = baseServo.read();
  recordShoulder[recordIndex]    = shoulderServo.read();
  recordElbow[recordIndex]       = elbowServo.read();
  recordWristPitch[recordIndex]  = wristPitchServo.read();
  recordWristRoll[recordIndex]   = wristRollServo.read();
  recordGripper[recordIndex]     = gripperServo.read();
}

// ------- Play Back Recorded Motion -------
void playMotion() {
  if (recordIndex == 0) {
    Serial.println("No motion recorded.");
    return;
  }

  Serial.println("Playing recorded motion...");

  int prevBase = baseServo.read();
  int prevShoulder = shoulderServo.read();
  int prevElbow = elbowServo.read();
  int prevWristPitch = wristPitchServo.read();
  int prevWristRoll = wristRollServo.read();
  int prevGripper = gripperServo.read();

  for (int i = 0; i < recordIndex; i++) {
    smoothMove(baseServo,        prevBase,        recordBase[i]);
    smoothMove(shoulderServo,    prevShoulder,    recordShoulder[i]);
    smoothMove(elbowServo,       prevElbow,       recordElbow[i]);
    smoothMove(wristPitchServo,  prevWristPitch,  recordWristPitch[i]);
    smoothMove(wristRollServo,   prevWristRoll,   recordWristRoll[i]);
    smoothMove(gripperServo,     prevGripper,     recordGripper[i]);

    prevBase = recordBase[i];
    prevShoulder = recordShoulder[i];
    prevElbow = recordElbow[i];
    prevWristPitch = recordWristPitch[i];
    prevWristRoll = recordWristRoll[i];
    prevGripper = recordGripper[i];

    delay(50);
  }

  Serial.println("Playback complete.");
}

// ------- Setup -------
void setup() {
  Serial.begin(115200);

  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  elbowServo.attach(ELBOW_PIN);
  wristPitchServo.attach(WRIST_PITCH_PIN);
  wristRollServo.attach(WRIST_ROLL_PIN);
  gripperServo.attach(GRIPPER_PIN);

  Serial.println("Record & Play Ready.");
  Serial.println("Commands:");
  Serial.println("R = Start Recording");
  Serial.println("S = Stop Recording");
  Serial.println("P = Play Motion");
}

// ------- Loop -------
void loop() {

  // Serial Commands
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'R') {
      Serial.println("Recording started...");
      isRecording = true;
      recordIndex = 0;
    }

    else if (cmd == 'S') {
      Serial.println("Recording stopped.");
      isRecording = false;
    }

    else if (cmd == 'P') {
      Serial.println("Playing motion...");
      isRecording = false;
      playMotion();
    }
  }

  // Recording Logic
  if (isRecording && recordIndex < MAX_STEPS) {
    capturePose();
    recordIndex++;
    delay(sampleInterval); 
  }
}
