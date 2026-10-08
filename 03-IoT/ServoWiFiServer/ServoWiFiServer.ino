
#include "WiFiEsp.h"
#include <Servo.h>

// Dados da rede WiFi
char ssid[] = "IFRS-ALUNOS";
char pass[] = "ifrsfarroupilha";

// Criando o objeto para a criação de um Servidor Web na porta 80
WiFiEspServer server(80);

String requisicao;
Servo myservo;
int pos = 1;

void setup()
{
  Serial.begin(9600);

  // Inicializando a comunicacao com o ESP8266
  Serial1.begin(115200);
  WiFi.init(&Serial1);

  // Conectando a rede WiFi
  Serial.print("Connecting to WiFi network: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
  }

  Serial.println("Connected to WiFi!");

  // Inicializando o Servo Motor
  myservo.attach(9);
  myservo.write(pos);

  // Inicializando o servidor Web
  server.begin();
  Serial.print("Server is at IP address: ");
  Serial.println(WiFi.localIP());

  requisicao = "";
}

void loop() {

  // Detectando a solicitacao de conexao de um cliente
  WiFiEspClient client = server.available();

  if (client) {
    boolean currentLineIsBlank = true;

    // Leitura dos dados da requisicao do cliente
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        requisicao += c;

        if (c == '\n' && currentLineIsBlank) {
          Serial.println(requisicao);

          // Detectando o valor do argumento da URL
          // para controlar a posicao do Servo Motor
          int inicio = requisicao.indexOf("GET /?graus=");

          if (inicio != -1) {
            inicio += 12;

            int fim = requisicao.indexOf(' ', inicio);
            String posStr = requisicao.substring(inicio, fim);

            pos = constrain(posStr.toInt(), 0, 180);

            myservo.write(pos);

            Serial.print("Setando posicao do servo para: ");
            Serial.println(pos);

            delay(15);
          }

          // Envia HTML de resposta ao cliente
          enviaResposta(client, pos);

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

    // Finalizando a conexao HTTP
    delay(1);
    client.stop();

    Serial.println("Client disconnected");
    Serial.println("");

    requisicao = "";
  }
}

// Funcao para enviar o HTML com formulario
// para controle do Servo Motor
void enviaResposta(WiFiEspClient client, int pos) {

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("");

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("O servo esta na posicao ");
  client.println(pos);
  client.println("<br><br>");

  client.println("<form>");
  client.println("<input required name=\"graus\" type=\"number\" min=\"0\" max=\"180\"/>");
  client.println("<input type=\"submit\" value=\"Enviar\">");
  client.println("</form>");

  client.println("</html>");
}
