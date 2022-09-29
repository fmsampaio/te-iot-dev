/* 
  Exemplo: 01-Basics/Blink  
*/


// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização do pino 13 (led built-in) como output (saída)
  pinMode(13, OUTPUT);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  digitalWrite(13, HIGH);         // Liga o LED  (HIGH é o nível alto de tensão)
  delay(1000);                    // Espera por 1 segundo (1000 milissegundos)
  digitalWrite(13, LOW);          // Desliga o LED (LOW é o nível baixo de tensão)
  delay(1000);                    // Espera por 1 segundo (1000 milissegundos)
}