#define TRIG 12
#define ECHO 13

long duration;
float distance;

void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // Clear TRIG
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  // Send 10µs pulse
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read echo time
  duration = pulseIn(ECHO, HIGH);

  // Convert to distance (cm)
  distance = duration * 0.034 / 2;

  // Print result
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}