#include "WiFiEsp.h"

// Dados da rede Wi-Fi
char ssid[] = "TP-Link_72F8";
char pass[] = "07898143";

// Criando o objeto para a criação de um Servidor Web na porta 80
WiFiEspServer server(80);

int pinoLED = 13;
int estadoLED;

void setup()
{
  Serial.begin(9600);

  // Inicializando comunicação serial com o ESP8266
  Serial1.begin(115200);
  WiFi.init(&Serial1);

  // Conectando à rede WiFi
  Serial.print("Connecting to WiFi network: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
  }

  Serial.println("Connected to WiFi!");

  pinMode(pinoLED, OUTPUT);

  // Inicializando o servidor Web e imprimindo o IP da interface de rede
  server.begin();
  Serial.print("Server is at IP address: ");
  Serial.println(WiFi.localIP());

  estadoLED = LOW;

  digitalWrite(pinoLED, estadoLED);
}

void loop() {

  // Detectando a solicitação de conexão de um cliente
  WiFiEspClient client = server.available();

  if (client) {
    boolean currentLineIsBlank = true;
    String requisicao;

    // Leitura dos dados da requisição do cliente
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        requisicao += c;

        if (c == '\n' && currentLineIsBlank) {
          Serial.print(requisicao);

          // Detectando o path da requisição para controlar o LED
          if (requisicao.indexOf("GET /LED=ON") != -1) {
            estadoLED = HIGH;
          }

          if (requisicao.indexOf("GET /LED=OFF") != -1) {
            estadoLED = LOW;
          }

          digitalWrite(pinoLED, estadoLED);

          if (estadoLED == HIGH) {
            Serial.println("LED LIGADO!");
          }
          else {
            Serial.println("LED DESLIGADO!");
          }

          // Envia HTML de resposta ao cliente
          enviaResposta(client);
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    // Finalizando a conexão HTTP
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
    requisicao = "";
  }
}

// Função para enviar o HTML com links para o controle do LED
void enviaResposta(WiFiEspClient client) {

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");

  if (estadoLED == HIGH) {
    client.print("On");
  }
  else {
    client.print("Off");
  }

  client.println("<br><br>");

  client.println("<a href=\"/LED=ON\"><button>Turn On</button></a>");
  client.println("<a href=\"/LED=OFF\"><button>Turn Off</button></a><br />");

  client.println("</html>");
}