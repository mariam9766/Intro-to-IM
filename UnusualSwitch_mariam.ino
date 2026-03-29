const int trigPin=12; // Pin number 12 on Arduino, receives echo pulse
const int echoPin=13; // Pin number 13 on Arduino, sends trigger pulse

int led1=2; // Pin number 2 on Arduino, recieve output for green pin
int led2=3; // Pin number 3 on Arduino, recieve output for red pin

int duration=0; // Initial variable for time of sensor
int distance=0; // Initial varianle for distance from sensor

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT); // Recieve output
  pinMode(echoPin,INPUT); // Recieve input
  pinMode(led1, OUTPUT);
  pinMode(led2,OUTPUT);
  Serial.begin(9600); // Ensure serial communication throught Arduino board
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin,HIGH); // Accept output
delay(1000); // 1 second break
digitalWrite(trigPin,LOW); // Not accept extra output
digitalWrite(led1,LOW); // Return to initial state before going into condition
digitalWrite(led2,LOW);

duration=pulseIn(echoPin,HIGH); // Echo recieve input at pin 13
distance=(duration/2)/28.5; // Calculation to find distance from sensor and load output

if (distance<10){
  digitalWrite(led1, HIGH); // If distase from sensor is less than 15, light up led 1, green light
}
else if (distance>=10){
  digitalWrite(led2, HIGH); // If distance is more than 10, light up led 2, red light

}
  
Serial.println(distance); //  Print the distance to check accuracy
}