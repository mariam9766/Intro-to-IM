// Button for confirming selections
const int buttonPin = 2;

// Joystick for navigating between options
const int joystickXPin = A0;

// Ultrasonic sensor for detecting hand movement
const int trigPin = 9;
const int echoPin = 10;

// LED pins for feedback
const int redLED = 3;
const int greenLED = 4;
const int yellowLED = 6;

// Timing control to avoid repeated signals
unsigned long lastButtonTime = 0;
unsigned long lastJoystickTime = 0;
unsigned long lastMotionTime = 0;

// Delay thresholds for each interaction
const int buttonDelay = 300;
const int joystickDelay = 350;
const int motionDelay = 200;

// Joystick thresholds (left & right movement range)
const int joystickLeftThreshold = 350;
const int joystickRightThreshold = 700;

// Motion detection thresholds
const int minMotionDistance = 5;
const int maxMotionDistance = 40;
const int motionChangeThreshold = 3;

// Ultrasonic timeout to prevent blocking
const int ultrasonicTimeout = 30000;

// State tracking variables
bool lastButtonState = HIGH;
int lastDistance = 0;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
}

// Measure distance using ultrasonic sensor
long detectDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, ultrasonicTimeout);
  return duration * 0.03 / 2;
}

// Receive LED commands from p5
void readSerial() {
  if (Serial.available() > 0) {
    char incoming = Serial.read();
    setLED(incoming);
  }
}

// Control LED based on p5 state
void setLED(char ledState) {
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  // Turn on the LED that corresponds to the current state
  if (ledState == 'R') {
    digitalWrite(redLED, HIGH);  // Action started
  } else if (ledState == 'Y') {
    digitalWrite(yellowLED, HIGH);  // Action in progress
  } else if (ledState == 'G') {
    digitalWrite(greenLED, HIGH);  // Action completed
  }
}

void loop() {
  readSerial();

  // Button press detection, sends once per press
  bool buttonState = digitalRead(buttonPin);

  // Send "B" to p5 once when the button is pressed to prevent repeated signals
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastButtonTime > buttonDelay) {
    Serial.println("B");
    lastButtonTime = millis();
  }

  lastButtonState = buttonState;

  // Joystick left & right navigation
  int joystickX = analogRead(joystickXPin);

  // Send "L" or "R" when joystick passes threshold, using delay to avoid rapid repeated signals
  if (millis() - lastJoystickTime > joystickDelay) {
    if (joystickX < joystickLeftThreshold) {
      Serial.println("L");
      lastJoystickTime = millis();
    } else if (joystickX > joystickRightThreshold) {
      Serial.println("R");
      lastJoystickTime = millis();
    }
  }

  // Movement detection using ultrasonic sensor
  int distance = detectDistance();
  int difference = abs(distance - lastDistance);

  // Send "M" when an object is within range and its distance changes enough to indicate movement
  if (millis() - lastMotionTime > motionDelay) {
    if (distance > minMotionDistance && distance < maxMotionDistance && difference > motionChangeThreshold) {
      Serial.println("M");
      lastMotionTime = millis();
    }

    lastDistance = distance;
  }
}