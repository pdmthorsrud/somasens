void setup() {
    // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
}

void left() {
    analogWrite(3, 1000);
    delay(100);
    analogWrite(5, 1000);
    delay(100);
    analogWrite(6, 1000);
    delay(100);
    analogWrite(9, 1000);
    delay(100);
}

void loop() {
    // put your main code here, to run repeatedly:
    left()
}