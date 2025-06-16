int const MIDDLE=3;
int const PINKY=5;
int const POINTER=6;
int const RING=9;

void setup() {
  // setup code, runs once:
  pinMode(PINKY, OUTPUT);
  pinMode(RING, OUTPUT);
  pinMode(MIDDLE, OUTPUT);
  pinMode(POINTER, OUTPUT);
}

void loop() {
  // continuous logic, runs as a while true loop:
  turn_on_all();
  delay(10);
  turn_off_all();
  digitalWrite(RING, LOW);
  delay(1000);
}

void turn_on_all() {
  digitalWrite(PINKY, HIGH);
  digitalWrite(RING, HIGH);
  digitalWrite(MIDDLE, HIGH);
  digitalWrite(POINTER, HIGH);
}

void turn_off_all() {
  digitalWrite(PINKY, LOW);
  digitalWrite(RING, LOW);
  digitalWrite(MIDDLE, LOW);
  digitalWrite(POINTER, LOW);
}

void rampup(int pin, int steps) {
  int intensity;
  intensity = 0;
  while (intensity < 355) {
    analogWrite(pin, intensity);
    intensity = intensity + steps;
    delay(50);
  }
  turn_off_all();
}

void flash(int on_time) {
  digitalWrite(PINKY, HIGH);
  digitalWrite(RING, HIGH);
  digitalWrite(MIDDLE, HIGH);
  digitalWrite(POINTER, HIGH);
  delay(on_time);
  turn_off_all();
}

void left(int on_time, int off_time) {
    digitalWrite(PINKY, HIGH);
    delay(on_time);
    digitalWrite(PINKY, LOW);
    delay(off_time);
    digitalWrite(RING, HIGH);
    delay(on_time);
    digitalWrite(RING, LOW);
    delay(off_time);
    digitalWrite(MIDDLE, HIGH);
    delay(on_time);
    digitalWrite(MIDDLE, LOW);
    delay(off_time);
    digitalWrite(POINTER, HIGH);
    delay(on_time);
    turn_off_all();
}

void right(int on_time, int off_time) {
    digitalWrite(POINTER, HIGH);
    delay(on_time);
    digitalWrite(POINTER, LOW);
    delay(off_time);
    digitalWrite(MIDDLE, HIGH);
    delay(on_time);
    digitalWrite(MIDDLE, LOW);
    delay(off_time);
    digitalWrite(RING, HIGH);
    delay(on_time);
    digitalWrite(RING, LOW);
    delay(off_time);
    digitalWrite(PINKY, HIGH);
    delay(on_time);
    turn_off_all();
}