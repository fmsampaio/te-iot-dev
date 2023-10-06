/* 
  Exemplo: 02-Components/RFIDSimple
*/
 
// Inclui a biblioteca padrão do Arduino para barramentos SPI
#include <SPI.h>
// Inclui biblioteca para manipulação do sensor RFID
#include <RFID.h>

// Define as conexões de IO para os pinos SDA e RST
#define SDA_DIO 9
#define RESET_DIO 8

// Cria uma instância do projeto RFID
RFID RC522(SDA_DIO, RESET_DIO); 

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() { 
  // Inicialização da comunicação serial (9600 bps)
  Serial.begin(9600);

  // Habilita e interface SPI
  SPI.begin(); 
  
  // Inicializa o sensor RFID
  RC522.init();
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // Checa se um cartão/tag RFID foi detectado
  if (RC522.isCard())
  {
    // Encontra o ID do cartão/tag
    RC522.readCardSerial();
    Serial.println("Card detected:");

    String idRFID = getID(RC522.serNum);
    Serial.print("ID: ");
    Serial.println(idRFID);

    Serial.println();
  }
  delay(1000);
}

String getID(unsigned char serNum[5]) {
    String returnable = "";
    for(int i = 0; i < 5; i++) { // Impressão do ID do cartão/tag em decimal
      returnable += serNum[i];
    }
    return returnable;
}
