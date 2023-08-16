#include <PushButton.h>

PushButton btn(2);
int ledPin = 13;

bool estadoLed = true;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(btn.pressionadoPorPulso()) {
    estadoLed = ! estadoLed;
  }

  if(estadoLed) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

}