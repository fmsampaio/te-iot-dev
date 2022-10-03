/* 
  Exemplo: 02-Components/Servo
*/

#include <Servo.h>

Servo myservo;  // Cria um objeto para controle do servo motor

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  //Associa a porta 9 ao servo motor (output)
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

// A função loop é executada de forma repetida sem parada
void loop() {
  myservo.write(0);  //Posiciona o servo motor na angulação 0 graus
  delay(1000);       //Insere delay de 1s
  myservo.write(90); //Posiciona o servo motor na angulação 90 graus
  delay(1000);       //Insere delay de 1s
  myservo.write(180);//Posiciona o servo motor na angulação 180 graus
  delay(1000);       //Insere delay de 1s
  myservo.write(90); //Posiciona o servo motor na angulação 90 graus
  delay(1000);       //Insere delay de 1s
}

 
   