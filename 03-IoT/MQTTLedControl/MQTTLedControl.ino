/*
  Exemplo: 03-IoT/MQTTSimple
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// TODO: cada bancada deve ter um MAC address diferente
byte mac[]    = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED}; //TODO modificar aqui!!

/** Plano A => MQTT Eclipse Projects**/
String server = "mqtt.eclipseprojects.io";
int port = 1883;

/** Plano B => Public MQTT HQ **/
//String server = "public.mqtthq.com";
//int port = 1883;

String ledTopic = "te/ledXX";
String clientName = "arduinoClientXX"; //TODO modificar aqui! Cada cliente MQTT deve ter um nome único!

int ledPin = 13;

// Aqui são tratadas as mensagens que são recebidas do servidor MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  
  for (int i=0;i<length;i++) {
    message += (char)payload[i];
  }

  String topicStr(topic);
  Serial.println(message);

  if(topicStr.equals(ledTopic)) {
    if(message.equals("1")) {
      digitalWrite(ledPin, HIGH);
    }
    else if(message.equals("0")) {
      digitalWrite(ledPin, LOW);
    }
    else {
      Serial.println("Command not recognized...");
    }
  }

}

// Criação e inicialização dos objetos para a criação de um cliente MQTT
EthernetClient ethClient;
PubSubClient client(ethClient);

// Função para criação da conexão com o MQTT Broker
void connectToMQTTBroker() {

  // Tentativa (de forma repetida) de conexão
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
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
  client.subscribe(ledTopic.c_str()); //TODO: modificar sufixo do nome do tópico
}

void setup()
{
  Serial.begin(9600);

  // Inicializando o Ethernet Shield
  Ethernet.begin(mac);
  delay(1500);

  Serial.println("Interface ethernet iniciada...");

  // Setando informações do Broker MQTT e da função de callback
  client.setServer(server.c_str(), port);
  client.setCallback(callback);

  connectToMQTTBroker();
  subscribeToTopics();

  pinMode(ledPin, OUTPUT);
  
}

void loop()
{
  if(!client.connected()) {
    connectToMQTTBroker();
    subscribeToTopics();
  }

  client.loop();
}
