/* 
  Exemplo: 01-Basics/AnalogReadSerial  
*/

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização da comunicação serial (9600 bps)
  Serial.begin(9600);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // Leitura do pino analógico A0 (valores entre 0 e 1023)
  int sensorValue = analogRead(A0);
  // Impressão do valor lido por meio do pino analógico
  Serial.println(sensorValue);
  delay(1);        // Delay entre leituras para estabilidade
}
