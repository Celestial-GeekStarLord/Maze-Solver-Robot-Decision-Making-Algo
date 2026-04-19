#include <Servo.h>
#include <Ultrasonic.h>

// ---------------- SENSOR ----------------
const int trigPin = 2;
const int echoPin = 3;

Ultrasonic ultrasonic(trigPin, echoPin);

// ---------------- SERVO ----------------
Servo myServo;
const int servoPin = 6;

// Servo angles
const int LOOK_LEFT = 170;
const int LOOK_FRONT = 90;
const int LOOK_RIGHT = 10;

// ---------------- MOTOR PINS (L298N) ----------------
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 11;
const int IN4 = 12;

// ---------------- DISTANCE THRESHOLD ----------------
const int OBSTACLE_DIST = 15;

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Servo
  myServo.attach(servoPin);
  myServo.write(LOOK_FRONT);

  delay(1000);
}

// ---------------- MAIN LOOP ----------------
void loop() {

  int frontDist = readDistance(LOOK_FRONT);

  if (frontDist > OBSTACLE_DIST) {
    // Path is clear → move forward
    moveForward();
  } 
  else {
    // obstacle ahead → check sides
    stopMotors();
    delay(200);

    int leftDist = readDistance(LOOK_LEFT);
    delay(200);
    int rightDist = readDistance(LOOK_RIGHT);

    if (leftDist > rightDist && leftDist > OBSTACLE_DIST) {
      turnLeft();
    }
    else if (rightDist > OBSTACLE_DIST) {
      turnRight();
    }
    else {
      // dead end → go back
      moveBackward();
      delay(500);
      turnRight();
    }
  }
}

// ---------------- SENSOR FUNCTION ----------------
int readDistance(int angle) {
  myServo.write(angle);
  delay(300); // allow servo to reach position
  int d = ultrasonic.Ranging(CM);

  Serial.print("Angle ");
  Serial.print(angle);
  Serial.print(" Distance: ");
  Serial.println(d);

  return d;
}

// ---------------- MOVEMENT FUNCTIONS ----------------
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(400);
  stopMotors();
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(400);
  stopMotors();
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}