#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>

// TODO: cada bancada deve ter um MAC address diferente
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE4 }; 

// Criando o objeto para a criação de um Servidor Web na porta 80
EthernetServer server(80);                             
 
String requisicao;
Servo myservo; 
int pos = 1; 
 
void setup()
{
  Serial.begin(9600);

// Inicializando o Ethernet Shield
  Ethernet.begin(mac);
  myservo.attach(9); 

  server.begin();
  Serial.print("Server is at IP address: ");
  Serial.println(Ethernet.localIP());

  requisicao = "";
}
 
void loop() {

  // Detectando a solicitação de conexão de um cliente
  EthernetClient client = server.available();

  if (client) { 
    boolean currentLineIsBlank = true;
    
    // Leitura dos dados da requisição do cliente
    while (client.connected()) {
      
      if (client.available()) { 
        char c = client.read(); 
        requisicao += c;
        
        if (c == '\n' && currentLineIsBlank ) {     
          Serial.println(requisicao);
          
          // Detectando o valor do argumento da URL para controlar a posição do Servo Motor
          if (requisicao.indexOf("GET /?graus=") != -1)  {
            String posStr = requisicao.substring(12, 15);
            pos = posStr.toInt();
            
            myservo.write(pos);   
            Serial.print("Setando posição do servo para: ");         
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
    
    // Finalizando a conexão HTTP
    delay(1);
    client.stop();  
    Serial.println("Client disconnected");
    Serial.println("");
    requisicao = ""; 
  }
}

// Função para enviar o HTML com links para o controle do LED
void enviaResposta(EthernetClient client, int pos) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("O servo esta na posicao ");
  client.println(pos);
  client.println("<br><br>");
  client.println("<form>");
  client.println("<input required name=\"graus\" type=\"number\"/>"); 
  client.println("<input type=\"submit\" value=\"Enviar\">");
  client.println("</form>");
  client.println("</html>");
}