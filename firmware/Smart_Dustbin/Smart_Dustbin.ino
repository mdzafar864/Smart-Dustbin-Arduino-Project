#include <Servo.h>

Servo lidServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

const int openAngle = 90;
const int closeAngle = 0;

const int detectDistance = 20;

long duration;
float distance;

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.0343 / 2;
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lidServo.attach(servoPin);

  // Start with lid closed
  lidServo.write(closeAngle);
  delay(1000);
}

void loop() {

  distance = getDistance();

  if (distance < 0) {
    Serial.println("No Echo");
    delay(200);
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Detect hand
  if (distance <= detectDistance && distance > 0) {

    Serial.println("Hand Detected!");
    Serial.println("Opening Lid...");

    // Open lid
    lidServo.write(openAngle);

    // Keep lid open for 5 seconds
    delay(5000);

    Serial.println("Closing Lid...");

    // Close lid
    lidServo.write(closeAngle);

    // Wait before checking again
    delay(2000);

    Serial.println("Ready");
  }

  delay(200);
}
