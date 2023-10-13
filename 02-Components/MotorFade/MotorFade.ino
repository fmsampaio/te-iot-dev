/*Pinagem do arduino*/
//motor_A
int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeA = 3;

//Inicializa Pinos
void setup(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(velocidadeA,OUTPUT);

  Serial.begin(9600);
}

void loop(){
  /*Exemplo de velocidades no motor A*/
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  Serial.println("Sentido anti-horário!");

  int velocidade;
  for(velocidade = 0; velocidade < 255; velocidade += 10) {
    Serial.print("Velocidade: ");
    Serial.println(velocidade);
    analogWrite(velocidadeA,velocidade);
    delay(500);
  }

  /*Exemplo de velocidades no motor A*/
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  Serial.println("Sentido HORÁRIO!");

  for(velocidade = 255; velocidade > 0; velocidade -= 10) {
    Serial.print("Velocidade: ");
    Serial.println(velocidade);
    analogWrite(velocidadeA,velocidade);
    delay(500);
  }
  
}