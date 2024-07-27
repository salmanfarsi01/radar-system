#include <Servo.h>

// Define the pin numbers for the laser, buzzer, ultrasonic sensor, and servo
int laserPin = 9;
int buzzerPin = 8;
int trigPin = 7;
int echoPin = 6;
int servoPin = 10;

// Define the threshold distance to detect objects (in centimeters)
 int thresholdDistance = 20; // Distance in cm

Servo myServo;  // Create a servo object

// Variables to keep track of the servo position and direction
int servoPosition = 15;
int servoDirection = 1; // 1 for increasing, -1 for decreasing

void setup() {
  // Initialize the laser and buzzer pins as outputs
  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach the servo to the servo pin
  myServo.attach(servoPin);
  
  // Start with the laser and buzzer turned off
  digitalWrite(laserPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin and calculate the distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  // Print the distance to the serial monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if the distance is less than or equal to the threshold distance
  if (distance > 0 && distance <= thresholdDistance) {
    // Turn the laser on and buzzer off
    digitalWrite(laserPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    delay(2000);
  } else {
    // Turn the laser off and buzzer on
    digitalWrite(laserPin, LOW);
    digitalWrite(buzzerPin, HIGH);
  }

  // Update the servo position
  myServo.write(servoPosition);
  
  // Increment or decrement the servo position
  servoPosition += servoDirection;
  
  // Reverse direction if the servo reaches the end points
  if (servoPosition >= 165 || servoPosition <= 15) {
    servoDirection = -servoDirection;
  }
  
  // Wait before taking the next measurement
  delay(30);
}
