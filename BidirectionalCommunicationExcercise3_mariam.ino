int ledPin = 2;  // LED that flashes on bounce connected to pin 2

void setup() {
  // Start serial communication so we can send data
  // over the USB connection to our p5js sketch
  Serial.begin(9600);

  // We'll use the builtin LED as a status output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Outputs on the pin
  pinMode(ledPin, OUTPUT);

  // Blink them so we can check the wiring
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);

  // start the handshake
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
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH);  // led on while receiving data

    int bounce = Serial.parseInt();  // to receive bounce value, 0 or 1

    if (Serial.read() == '\n') {

      // if the ball bounces, flash LED
      if (bounce == 1) {
        digitalWrite(ledPin, HIGH);
        delay(150);  // for flash effect
        digitalWrite(ledPin, LOW);
      }


      //SEND TO P5
      int sensor = analogRead(A0);
      delay(5);
      Serial.println(sensor);
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}
