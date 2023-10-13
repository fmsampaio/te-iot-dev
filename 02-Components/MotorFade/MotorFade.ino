/*Pinagem do arduino*/
//motor_A
int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeA = 3;

//variavel auxiliar
int velocidade = 0;
//Inicializa Pinos
void setup(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(velocidadeA,OUTPUT);
}

void loop(){
  /*Exemplo de velocidades no motor A*/
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

 
  //velocidade de 0 a 255
  while (velocidade < 255){
    analogWrite(velocidadeA,velocidade);
    velocidade = velocidade + 10;
    delay(50);
  }
  //velocidade de 255 a 0
  while (velocidade > 0){
    analogWrite(velocidadeA,velocidade);
    velocidade = velocidade - 10;
    delay(50);
}
}