/* 
  Exemplo: 02-Components/ServoControl
*/

#include <Servo.h>

Servo myservo;  // Cria um objeto para controle do servo motor

int potpin = A0;  // Pino analógico utilizado para conectar o potenciômetro
int val;    // Variável para ler o valor do pino A0

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  //Associa a porta 9 ao servo motor (output)
  myservo.attach(9); 
  Serial.begin(9600);
}

// A função loop é executada de forma repetida sem parada
void loop() {
 val = analogRead(potpin);            // Leitura do valor de entrada do potenciômetro (de 0 a 1023)
 Serial.println(val);
 val = map(val, 0, 1023, 0, 180);     // Troca a escala do valor para ser enviado ao servo motor (de 0 a 180)
 myservo.write(val);                  // Seleciona a angulação do servo motor de acordo com o resultado da conversão de escalas
 delay(15);                           // Adiciona uma espera para o servo motor se movimentar
}

   