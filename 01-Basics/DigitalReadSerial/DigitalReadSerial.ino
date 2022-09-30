/* 
  Exemplo: 01-Basics/Blink  
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização da comunicação serial (9600 bps)
  Serial.begin(9600);
  // Inicialização do botão como input (entrada)
  pinMode(pushButton, INPUT);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // Leitura do pino de entrada
  int buttonState = digitalRead(pushButton);
  // Impressão (via monitor serial) do valor referente ao pino de entrada
  Serial.println(buttonState);
  delay(1);        // Inserção de delay pequeno para estabilidade na leitura
}
