int ledPin = 3;  // connect LED to PWM pin 3

void setup() {
  Serial.begin(9600); // start serial communication 

  pinMode(LED_BUILTIN, OUTPUT);  // builtin LED as a status output.
  pinMode(ledPin, OUTPUT);       // outputs on pin

  // blink to check the wiring
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);

  // start handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH);  // on/blink while waiting for serial data
    Serial.println("0");              // send a starting message
    delay(300);                       // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
  // wait for data from p5 before doing something
  if (Serial.available() > 0) {

    digitalWrite(LED_BUILTIN, HIGH);  // led on while receiving data

    int ledValue = Serial.parseInt();  // brightness value from p5

    if (Serial.read() == '\n') { // end of message check
      ledValue = constrain(ledValue, 0, 255); // keep brightness between 0 and 255

      analogWrite(ledPin, ledValue);  // control brightness
    }

    digitalWrite(LED_BUILTIN, LOW);
  }
}
