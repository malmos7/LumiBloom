#include <Servo.h>

// === Pin Assignments ===
const int servoPin = 9;        // Servo motor pin
const int pirPin = 7;          // PIR motion sensor output
const int ldrPin = 6;          // LDR module digital output
const int resetPin = 2;        // Reset button
const int lightPin_1_2 = 5;    // Controls Fairy Lights 1 and 2
const int lightPin_3_4 = 11;   // Controls Fairy Lights 3 and 4

// === Servo and Light Control ===
Servo flowerServo;

int servoPosition = 0;          // Current servo angle
const int SERVO_OPEN = 90;      // Open position
const int SERVO_CLOSED = 0;     // Closed position

// === Timers ===
unsigned long lastMotionTime = 0;
const unsigned long t_wait = 30UL * 1000UL;  // 30 seconds timeout for no motion

// === Modes (Finite State Machine) ===
#define MODE_SLEEPING 0
#define MODE_BLOOM 1
#define MODE_BLOOMING 2
#define MODE_BLOOMED 3
#define MODE_FADE 4
#define MODE_FADING 5
#define MODE_FADED 6

byte mode = MODE_SLEEPING;

// === Fairy Light Brightness ===
int lightBrightness = 0;   // 0 to 255
const int fadeStep = 5;    // How fast to fade

// ====================
// Setup
// ====================
void setup() {
  flowerServo.attach(servoPin);

  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(lightPin_1_2, OUTPUT);
  pinMode(lightPin_3_4, OUTPUT);

  analogWrite(lightPin_1_2, 0);
  analogWrite(lightPin_3_4, 0);
  
  flowerServo.write(SERVO_CLOSED);
}

// ====================
// Main Loop
// ====================
void loop() {
  unsigned long currentTime = millis();
  int motion = digitalRead(pirPin);
  int lightLevel = digitalRead(ldrPin);
  int resetButton = digitalRead(resetPin);

  // --- Manual Reset Button ---
  if (resetButton == LOW) {
    emergencyReset();
  }

  // --- Finite State Machine ---
  switch (mode) {
    case MODE_SLEEPING:
      if (motion == HIGH && lightLevel == HIGH) {
        changeMode(MODE_BLOOM);
      }
      break;

    case MODE_BLOOM:
      changeMode(MODE_BLOOMING);
      break;

    case MODE_BLOOMING:
      {
        boolean petalsOpen = openPetals();
        boolean lightsOn = fadeLightsUp();
        if (petalsOpen && lightsOn) {
          lastMotionTime = millis(); // Start timer once bloom finished
          changeMode(MODE_BLOOMED);
        }
      }
      break;

    case MODE_BLOOMED:
      if (motion == HIGH) {
        lastMotionTime = millis(); // Reset timer if motion
      }
      else if ((currentTime - lastMotionTime) > t_wait) {
        changeMode(MODE_FADE); // No motion for 30s ➔ close
      }
      break;

    case MODE_FADE:
      changeMode(MODE_FADING);
      break;

    case MODE_FADING:
      {
        boolean petalsClosed = closePetals();
        boolean lightsOff = fadeLightsDown();
        if (petalsClosed && lightsOff) {
          changeMode(MODE_FADED);
        }
      }
      break;

    case MODE_FADED:
      changeMode(MODE_SLEEPING);
      break;
  }

  delay(5); // Very small delay for smooth responsiveness
}

// ====================
// Helper Functions
// ====================

// Emergency Reset to immediately close flower
void emergencyReset() {
  flowerServo.write(SERVO_CLOSED);
  servoPosition = SERVO_CLOSED;
  lightBrightness = 0;
  
  analogWrite(lightPin_1_2, 0);
  analogWrite(lightPin_3_4, 0);
  
  mode = MODE_SLEEPING;
}

// Change FSM mode
void changeMode(byte newMode) {
  if (mode != newMode) {
    mode = newMode;
  }
}

// Smoothly open petals
boolean openPetals() {
  if (servoPosition >= SERVO_OPEN) {
    return true;
  }
  servoPosition++;
  flowerServo.write(servoPosition);
  delay(10); // Smooth movement
  return false;
}

// Smoothly close petals
boolean closePetals() {
  if (servoPosition <= SERVO_CLOSED) {
    return true;
  }
  servoPosition--;
  flowerServo.write(servoPosition);
  delay(10); // Smooth movement
  return false;
}

// Gradually fade lights ON
boolean fadeLightsUp() {
  if (lightBrightness >= 255) {
    analogWrite(lightPin_1_2, 255);
    analogWrite(lightPin_3_4, 255);
    return true;
  }
  lightBrightness += fadeStep;
  if (lightBrightness > 255) lightBrightness = 255;

  analogWrite(lightPin_1_2, lightBrightness);
  analogWrite(lightPin_3_4, lightBrightness);

  delay(5);
  return false;
}

// Gradually fade lights OFF
boolean fadeLightsDown() {
  if (lightBrightness <= 0) {
    analogWrite(lightPin_1_2, 0);
    analogWrite(lightPin_3_4, 0);
    return true;
  }
  lightBrightness -= fadeStep;
  if (lightBrightness < 0) lightBrightness = 0;

  analogWrite(lightPin_1_2, lightBrightness);
  analogWrite(lightPin_3_4, lightBrightness);

  delay(5);
  return false;
}

