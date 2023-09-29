// Declaração de variável global que vai receber os dados Bluetooth
char dados;

void setup() {
    // Inicializa as portas seriais do arduino
    Serial.begin(9600); // Porta utilizada para impressão no monitor serial
    Serial1.begin(9600); // Porta utilizada para comunicação com o Módulo HC-05
}

void loop(){

  // Verifica se existe algum dado disponível na serial 

  String mensagem = "";
  
  while(Serial1.available()>0){

    // Caso houver a variável dados recebe este valor 
    dados = Serial1.read();

    // Concatema novo dado recebido na String para compor a mensagem completa
    mensagem += dados;
    
    //Espera por 15 ms
    delay(15);
  }

  if(!mensagem.equals("")) {
    // Printa a mensagem recebida na serial
    Serial.print("Dados recebidos: ");
    Serial.println(mensagem);
  }

}