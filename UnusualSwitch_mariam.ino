const int trigPin=12; // Connected to trigger on sensor, attached to pin 12
const int echoPin=13; // Connected to echo on sensor, attached to pin 13

int led1=2; // Green LED, connected to pin number 2
int led2=3; // Red LED, connected to pin number 3

int duration=0; // Initial variable for time of echo pulse
int distance=0; // Initial variable for distance in cm

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin,OUTPUT); // Trigger pin sends pulse
  pinMode(echoPin,INPUT); // Echo pin receives pulse
  pinMode(led1, OUTPUT); // Green LED
  pinMode(led2,OUTPUT); // Red LED
  Serial.begin(9600); // Ensure serial communication through Arduino for debugging
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(trigPin,HIGH); // Send pulse to trigger sensor
delay(1000); // One second delay to trigger sensor 
digitalWrite(trigPin,LOW); // End trigger pulse

digitalWrite(led1,LOW); // Return green light to initial state before going into if else condition
digitalWrite(led2,LOW); // Return red light to initial state before going into if else condition

duration=pulseIn(echoPin,HIGH); // Read echo pulse duration
distance=(duration/2)/28.5; // Calculate distance in cm

if (distance<=10){
  digitalWrite(led1, HIGH); // If distance from sensor is equal or less than 10 cm, green light on
}
else if (distance>10){
  digitalWrite(led2, HIGH); // If distance is more than 10 cm, light up led 2, red light on
}
  
Serial.println(distance); //  Print the distance for debugging
}