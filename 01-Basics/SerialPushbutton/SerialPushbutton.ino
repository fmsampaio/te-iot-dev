/* 
  Exemplo: 01-Basics/SerialPushbutton  
*/

// Importação da biblioteca externa "PushButton"
#include <PushButton.h>

// Inicialização do objeto do tipo PushButton e associação ao pino 2 (input)
PushButton btn1(2);

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização da comunicação serial (9600 bps)
  Serial.begin(9600);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // Utilização da função para detecção de evento por NÍVEL no botão
  if(btn1.pressionadoPorNivel()) {
    Serial.println("Botao pressionado por NIVEL");
  }

  // Utilização da função para detecção de evento por PULSO no botão
  if(btn1.pressionadoPorPulso()) {
    Serial.println("Botao pressionado por PULSO");
  }
}
