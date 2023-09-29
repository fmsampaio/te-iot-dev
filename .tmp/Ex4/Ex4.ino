#include <Servo.h>

Servo servo; 

int btn1Pin = 2; 
int btn2Pin = 3;
int posicaoServo = 90;
int passoServo = 20;

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
  servo.attach(9);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  if(digitalRead(btn1Pin) == HIGH) {
    posicaoServo += passoServo;
  }
  if(digitalRead(btn2Pin) == HIGH) {
    posicaoServo -= passoServo;
  }

  posicaoServo = (posicaoServo > 180) ? 180 : posicaoServo;
  posicaoServo = (posicaoServo < 0) ? 0 : posicaoServo;

  servo.write(posicaoServo);

  delay(200);
}
