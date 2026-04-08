//Components:

// Analog:
int blueLed = 11;    // blue LED attached to PWM pin 11
int brightness = 0;  // declare and initialize brightness for smooth fading

// Digital:
const int yellowLed = 12;  // yellow LED attached to pin 12
const int buttonPin = 2;   // pushbutton attached to pin 2

int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState = 0;  // variable for storing the previous pushbutton state

bool ledState = false;  // track on and off status of the yellow LED

void setup() {

  // Analog:
  Serial.begin(9600);
  pinMode(blueLed, OUTPUT);  // initialize blue LED pin as an output

  // Digital:
  pinMode(yellowLed, OUTPUT);  // initialize yellow LED pin as an output
  pinMode(buttonPin, INPUT);   // initialize pushbutton pin as an input
}

void loop() {

  //Analog:
  int sensorValue = analogRead(A2); // read external light level from photoresistor
  sensorValue = constrain(sensorValue, 70, 230);              // constrain sensor to assigned range
  int targetBrightness = map(sensorValue, 70, 230, 255, 0);  // map sensor value to LED brightness range

  if (brightness < targetBrightness) { // gradually adjust brightness according to state
    brightness++;  // increase brightness slowly
  } else if (brightness > targetBrightness) {
    brightness--;  // decrease brightness slowly
  }

  analogWrite(blueLed, brightness);  // set brightness of blue LED
  Serial.println(sensorValue);       // track sensor values for debugging
  delay(50);                         // wait 60 milliseconds for dimming effect

  // Digital:
  buttonState = digitalRead(buttonPin);  // read current state of pushbutton

  if (buttonState == HIGH && lastButtonState == LOW) { // detect button press and allow transitioning
    ledState = !ledState;  // toggle yellow LED
  }

  digitalWrite(yellowLed, ledState);  // set yellow LED based on toggle state
  lastButtonState = buttonState;   // save current button state for next loop
}
