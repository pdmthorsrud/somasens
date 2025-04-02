 int const PINKY=3;
int const RING=5;
int const MIDDLE=6;
int const POINTER=9;

void setup() {
  // setup code, runs once:
  pinMode(PINKY, OUTPUT);
  pinMode(RING, OUTPUT);
  pinMode(MIDDLE, OUTPUT);
  pinMode(POINTER, OUTPUT);
}

void loop() {
  // continuous logic, runs as a while true loop:
  //digitalWrite(PINKY, HIGH);
  //delay(1000);
  //digitalWrite(PINKY, LOW);
  left(200,30);
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
    analogWrite(POINTER, 1000);
    delay(on_time);
    analogWrite(MIDDLE, 1000);
    delay(on_time);
    analogWrite(RING, 1000);
    delay(on_time);
    analogWrite(PINKY, 1000);
    delay(100);
    turn_off_all();
}