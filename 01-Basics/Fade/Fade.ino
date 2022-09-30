/*
  Exemplo: 01-Basics/Fade
*/

int led = 9;           // associar o pino 9 (PWM) ao LED
int brightness = 0;    // luminosidade do LED (8 bits - 0 a 255)
int fadeAmount = 5;    // passo do aumento/redução da luminosidade do LED

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização do pino 9 como output (saída)
  pinMode(led, OUTPUT);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // define o brilho do LED
  analogWrite(led, brightness);

  // atualiza o novo brilho do LED
  brightness = brightness + fadeAmount;

  // reverte o sentido do (de-)crescimento do brilho do LED
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // Espera por 30 ms para melhor visualização do efeito
  delay(30);
}
