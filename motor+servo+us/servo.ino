#include <Servo.h>

char command;

int IN1 = 9;
int IN2 = 10;
int IN3 = 11;
int IN4 = 12;

int trigPin = 7;
int echoPin = 6;

int servoPin = 5;
Servo myServo;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(90); // center position

  stopMotors();
}

void loop() {

  int frontDist = scanDistance(90);
  int rightDist = scanDistance(0);
  int leftDist  = scanDistance(180);

  Serial.print("F:");
  Serial.print(frontDist);
  Serial.print(" R:");
  Serial.print(rightDist);
  Serial.print(" L:");
  Serial.println(leftDist);

  // OBSTACLE CHECK
  if (frontDist < 15 || rightDist < 15 || leftDist < 15) {
    stopMotors();
    return;
  }

  // Manual control
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'w') forward();
    else if (command == 's') backward();
    else if (command == 'a') left();
    else if (command == 'd') right();
    else if (command == 'x') stopMotors();
  }
}

// Measure distance at servo angle
int scanDistance(int angle) {
  myServo.write(angle);
  delay(300); // allow servo to move

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

// MOVE FORWARD
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// MOVE BACKWARD
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// TURN LEFT
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// TURN RIGHT
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// STOP
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}