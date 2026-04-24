#include <Servo.h>

// ── Ultrasonic ───────────────────────────────
const int trigPin = 2;
const int echoPin = 3;

// ── Servo ───────────────────────────────────
Servo myServo;
const int servoPin = 6;

const int LOOK_LEFT  = 180;
const int LOOK_FRONT = 90;
const int LOOK_RIGHT = 0;

// ── Motor Pins ──────────────────────────────
const int IN1 = 8;
const int IN2 = 10;
const int IN3 = 11;
const int IN4 = 12;

// ── PWM Speed ───────────────────────────────
const int ENA = 9;
const int ENB = 5;



// ── Logic ───────────────────────────────────
const int OBSTACLE_DIST = 20;

// ───────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(LOOK_FRONT);

  stopMotors();
  delay(1000);
}

// ───────────────────────────────────────────
void loop() {

  int frontDist = getDistance();

  if (frontDist > OBSTACLE_DIST) {
    // move step by step
    moveForward();
    delay(600);

    stopMotors();
    delay(200);
  }
  else {
    // obstacle detected
    stopMotors();
    delay(300);

    // check LEFT
    myServo.write(LOOK_LEFT);
    delay(400);
    int leftDist = getDistance();

    // check RIGHT
    myServo.write(LOOK_RIGHT);
    delay(400);
    int rightDist = getDistance();

    // return front
    myServo.write(LOOK_FRONT);
    delay(300);

    Serial.print("L: "); Serial.print(leftDist);
    Serial.print(" | R: "); Serial.println(rightDist);

    // decision
    if (leftDist >= rightDist) {
      // LEFT priority (default)
      turnLeft();
    }
    else {
      turnRight();
    }
  }
}

// ═════════════════════════════════════════════
// ULTRASONIC
// ═════════════════════════════════════════════
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  return distance;
}

// ═════════════════════════════════════════════
// MOTOR CONTROL
// ═════════════════════════════════════════════
void setSpeed() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void moveForward() {
  setSpeed();

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward() {
  setSpeed();

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  setSpeed();

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(410);
  stopMotors();
}

void turnRight() {
  setSpeed();

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(410);
  stopMotors();
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}