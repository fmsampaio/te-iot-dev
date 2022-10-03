/* 
  Exemplo: 02-Components/BuzzerSimple
*/

// Pino ligado ao buzzer
int buzzer = 8;

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
    // Define o pino do Buzzer como Saida 
    pinMode(buzzer,OUTPUT);    
}

// A função loop é executada de forma repetida sem parada
void loop() {
    // Aciona o buzzer na frequencia relativa ao Dó em Hz
    tone(buzzer,261);    
    // Espera um tempo para Desativar
    delay(200);
    //Desativa o buzzer
    noTone(buzzer); 
    // Aciona o buzzer na frequencia relativa ao Ré em Hz   
    tone(buzzer,293);             
    delay(200);    
    noTone(buzzer); 
    // Aciona o buzzer na frequencia relativa ao Mi em Hz
    tone(buzzer,329);      
    delay(200);
    noTone(buzzer);     
    // Aciona o buzzer na frequencia relativa ao Fá em Hz
    tone(buzzer,349);    
    delay(200);    
    noTone(buzzer); 
    // Aciona o buzzer na frequencia relativa ao Sol em Hz
    tone(buzzer,392);            
    delay(200);
    noTone(buzzer); 
    delay(5000);
}

   