/* 
  Exemplo: 02-Components/Ultrassonic
*/

#include <Ultrasonic.h>

Ultrasonic ultrassom(8,7); //Inicializa o objeto para manipulação do sensor ultrassônico

long distance;

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
}

// A função loop é executada de forma repetida sem parada
void loop() {
  distance = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC)
  
  //imprime o valor da variável distancia
  Serial.print(distance); 
  Serial.println("cm");     
  
  delay(500); //Espera 0,5s entre cada leitura
}