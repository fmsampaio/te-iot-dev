/* 
  Exemplo: 02-Components/LDR  
*/

// Associa a porta analógica A5 ao LDR  
int portaLDR = A5; 

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização da comunicação serial (9600 bps)
  Serial.begin(9600);
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // Leitura do pino analógico A0 (valores entre 0 e 1023) - Sensor LDR
  int luminosity = analogRead(portaLDR); 

  // Impressão do valor de luminosidade lido pelo sensor
  Serial.println(luminosity);
  delay(1);        // Delay entre leituras para estabilidade
}

 
   