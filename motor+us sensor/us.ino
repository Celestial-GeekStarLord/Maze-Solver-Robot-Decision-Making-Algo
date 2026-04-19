char command;

int IN1 = 9;
int IN2 = 10;
int IN3 = 11;
int IN4 = 12;

int trigPin = 7;
int echoPin = 6;

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

  stopMotors();
}

void loop() {
  distance = getDistance();
  Serial.println(distance); // for debugging

  // Obstacle check
  if (distance > 0 && distance < 12) {
    stopMotors();
    return; // stop everything here
  }

  // Normal control
  if (Serial.available() > 0) {
    command = Serial.read();

    if (command == 'w') {
      forward();
    }
    else if (command == 's') {
      backward();
    }
    else if (command == 'a') {
      left();
    }
    else if (command == 'd') {
      right();
    }
    else if (command == 'x') {
      stopMotors();
    }
  }
}

// Ultrasonic distance function
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

// Move forward
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Move backward
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn left
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turn right
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}