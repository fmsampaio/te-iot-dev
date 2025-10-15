/*
  Exemplo: 03-IoT/MQTTSimple
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// TODO: cada bancada deve ter um MAC address diferente
byte mac[]    = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED}; //TODO modificar aqui!!

/** Plano A => Tyckr MQTT IO**/
String server = "mqtt.tyckr.io";
int port = 1883;

/** Plano B => Bevywise MQTT HQ **/
//String server = "public-mqtt-broker.bevywise.com";
//int port = 1883;

String ldrTopic = "te/ldrXX";
String clientName = "arduinoClientXX"; //TODO modificar aqui! Cada cliente MQTT deve ter um nome único!

int ldrPin = A0;

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

void setup()
{
  Serial.begin(9600);

  // Inicializando o Ethernet Shield
  Ethernet.begin(mac);
  delay(1500);

  Serial.println("Interface ethernet iniciada...");

  // Setando informações do Broker MQTT e da função de callback
  client.setServer(server.c_str(), port);

  connectToMQTTBroker();  
}

void publishLuminosity() {
  int luminosity = analogRead(ldrPin);
  String lumStr = String(luminosity);

  client.publish(ldrTopic.c_str(), lumStr.c_str());
  Serial.print("Message published [");
  Serial.print(ldrTopic);
  Serial.print("] --> ");
  Serial.println(luminosity);
}

void loop()
{
  if(!client.connected()) {
    connectToMQTTBroker();
    
  }
  publishLuminosity();
  delay(1000);

  client.loop();
}
