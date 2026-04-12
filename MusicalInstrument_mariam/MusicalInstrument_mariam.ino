#include "pitches.h"

int buzzerPin = 8;  // Buzzer pin

//Digital:

// Buttons:
int redPin = 2;
int bluePin = 3;
int yellowPin = 4;
int greenPin = 5;

//Notes:
int noteC = 262;  // Note C4 in pitches.h
int noteD = 294;  // Note D4
int noteE = 330;  // Note E4
int noteF = 349;  // Note F4

// Analog:

// the pin for the potentiometer
int potPin = A0;

// this will store the pot reading
int sensorValue = 0;

// this is gonna store the pitch after mapping
int pitch = 0;

void setup() {

  //Digital:

  // Assign buttons as inputs and buzzer as the output
  pinMode(redPin, INPUT);
  pinMode(bluePin, INPUT);
  pinMode(yellowPin, INPUT);
  pinMode(greenPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  //Analog:

  // start serial so we can see the values
  Serial.begin(9600);
}

void loop() {

  //Analog:

  // this reads how much the pot is turned
  sensorValue = analogRead(potPin);
  // this changes the pot range into a pitch range
  pitch = map(sensorValue, 0, 1023, 200, 2000);

  //Digital:

  if (digitalRead(redPin) == HIGH) {
    tone(buzzerPin, noteC * map(sensorValue, 0, 1023, 90, 105) / 100);  // Play note C when red button is pressed and adjust pitch without changing the note sound
  }

  else if (digitalRead(bluePin) == HIGH) {
    tone(buzzerPin, noteD * map(sensorValue, 0, 1023, 90, 105) / 100);  // Play note D when blue button is pressed and adjust pitch without changing the note sound
  }

  else if (digitalRead(yellowPin) == HIGH) {
    tone(buzzerPin, noteE * map(sensorValue, 0, 1023, 90, 105) / 100);  // Play note E when yellow button is pressed and adjust pitch without changing the note sound
  }

  else if (digitalRead(greenPin) == HIGH) {
    tone(buzzerPin, noteF * map(sensorValue, 0, 1023, 90, 105) / 100);  // Play note F when green button is pressed and adjust pitch without changing the note sound
  }

  else {
    noTone(buzzerPin);  // If no button is pressed, do not play anything
  }

  // Analog:

  // this prints the value to check it
  Serial.println(sensorValue);
  // a small delay so it doesn’t glitch
  delay(1);
}