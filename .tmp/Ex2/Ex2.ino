int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int valorPot = analogRead(A0);
  int brilhoLed = valorPot * 255 / 1023;

  analogWrite(ledPin, brilhoLed);
}
