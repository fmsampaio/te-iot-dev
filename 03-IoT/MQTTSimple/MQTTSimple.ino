/*
  Exemplo: 03-IoT/MQTTSimple
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

//TODO Atualizar valores do MAC e IP do servidor MQTT
byte mac[]    = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED}; //TODO modificar aqui!!

/** Local server **/
String server = "192.168.0.42";
int port = 1883;

/** MQTT TE Server **/
/*String server = "m14.cloudmqtt.com";
int port = 12891;
String username = "vqlvmcfj";
String password = "Vzw6NIX4voxY";
*/

String clientName = "arduinoClientFelipe"; //TODO modificar aqui!!

// Aqui são tratadas as mensagens que são recebidas do servidor MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  
  for (int i=0;i<length;i++) {
    message += (char)payload[i];
  }

  Serial.println(message);
}

// Criação e inicialização dos objetos para a criação de um cliente MQTT
EthernetClient ethClient;
PubSubClient client(ethClient);

int cont = 0;

// Função para criação da conexão com o MQTT Broker
void connectToMQTTBroker() {

  // Tentativa (de forma repetida) de conexão
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // TODO modificar aqui!!
    
    /*
    if (client.connect(clientName.c_str(), username.c_str(), password.c_str())) { 
    */

    if (client.connect(clientName.c_str())) {
    
      Serial.println("connected");
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("trying again in 5 seconds");
      // Aguarda 5 segundos antes de tentar novamente a conexão
      delay(5000);
    }
  }
  
}

//Aqui acontecem as inscrições em tópicos
void subscribeToTopics() {
  client.subscribe("test"); //TODO modificar aqui!!
}

void publishContagem() {
  String contStr(cont);
  Serial.println(contStr.c_str());
  client.publish("contagem",contStr.c_str()); 
  cont += 1;
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  delay(1500);

  Serial.println("Interface ethernet iniciada...");
  Serial.println(Ethernet.localIP());

  client.setServer(server.c_str(), port);
  client.setCallback(callback);

  connectToMQTTBroker();
  subscribeToTopics();
  
}

void loop()
{
  if(!client.connected()) {
    connectToMQTTBroker();
    subscribeToTopics();
  }
  publishContagem();

  client.loop();
}