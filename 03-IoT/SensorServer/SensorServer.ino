#include <SPI.h>
#include <Ethernet.h>

// TODO: cada bancada deve ter um MAC address diferente
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// Criando o objeto para a criação de um Servidor Web na porta 80
EthernetServer server(80);

void setup() {
  Serial.begin(9600);

  // Inicializando o Ethernet Shield
  Ethernet.begin(mac);

  // Inicializando o servidor Web e imprimindo o IP da interface de rede
  server.begin();
  Serial.print("Server is at IP address: ");
  Serial.println(Ethernet.localIP());
}


void loop() {

  // Detectando a solicitação de conexão de um cliente
  EthernetClient client = server.available();
  
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    // Leitura dos dados da requisição do cliente
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        if (c == '\n' && currentLineIsBlank) {
          // Envia HTML de resposta ao cliente
          enviaResposta(client);
          break;
        }
        
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // Finalizando a conexão HTTP
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}

void enviaResposta(EthernetClient client) {
  // Montando Header HTTP
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close"); 
  client.println("Refresh: 3");  // A página será recarregada automaticamente após 3 segundos
  client.println();
  client.println("<!DOCTYPE HTML>");
  // Montando o body da página HTML
  client.println("<html>");
  int sensorReading = analogRead(A0);
  client.print("analog input A0 is ");
  client.print(sensorReading);
  client.println("<br>");
  client.println("</html>");
}