// Definição dos pinos dos LEDs
#define D2  2
#define D3  3
#define D4  4

// Declaração de variável global que vai receber os dados Bluetooth
char dados;

void setup() {
    // Inicializa as portas seriais do arduino
    Serial.begin(9600); // Porta utilizada para impressão no monitor serial
    Serial1.begin(9600); // Porta utilizada para comunicação com o Módulo HC-05
    
    // Definição dos pinos dos LEDs como saída iniciando desligados
    pinMode(D2, OUTPUT);
    digitalWrite(D2, LOW);
    
    pinMode(D3, OUTPUT);
    digitalWrite(D3, LOW);
    
    pinMode(D4, OUTPUT);
    digitalWrite(D4, LOW);
}

void loop(){

    // Verifica se existe algum dado disponível na serial 
    while(Serial1.available()>0){
        // Caso houver a variável dados recebe este valor 
        dados = Serial1.read();
        // Printa o valor recebido na serial
        Serial.println(dados);
        //Espera por 15 ms
        delay(15);

        // Este trecho define qual LED deve acender ou apagar de acordo com o dado recebido
        // Se a letra recebida for maiuscula, o LED acende
        // Se a letra recebida for minuscula, o LED apaga
        switch(dados){
          case 'A':
          digitalWrite(D2, HIGH);
          break;
          
          case 'B':
          digitalWrite(D3, HIGH);
          break;
          
          case 'C':
          digitalWrite(D4, HIGH);
          break;          
          
          case 'a':
          digitalWrite(D2, LOW);
          break;
          
          case 'b':
          digitalWrite(D3, LOW);
          break;
          
          case 'c':
          digitalWrite(D4, LOW);
          break;
          
          default:
          break;
        }
    }
}