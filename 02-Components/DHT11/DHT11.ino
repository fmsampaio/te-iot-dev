/* 
  Exemplo: 02-Components/DHT11
*/

#include "DHT.h"

#define DHTPIN 2     // Pino digital conectado ao sensor DHT11
#define DHTTYPE DHT11   // Tipo de sensor: DHT 11

DHT dht(DHTPIN, DHTTYPE);  //Inicializa objeto para gerenciar o sensor

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup() {
  // Inicialização da comunicação serial (9600 bps)
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

// A função loop é executada de forma repetida sem parada
void loop() {
  // Espera 2s entre cada medição
  delay(2000);

  float h = dht.readHumidity();
  // Leitura da temperatura em Celsius (default)
  float t = dht.readTemperature();
  // Leitura da temperatura em Fahreinheit
  float f = dht.readTemperature(true);

  // Verifica se alguma leitura falhou e tenta novamente
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Computa o índice de calor (em Celsius)
  float hif = dht.computeHeatIndex(f, h);
  // Computa o índice de calor (em Fahreinheit)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("C ");
  Serial.print(f);
  Serial.print("F  Heat index: ");
  Serial.print(hic);
  Serial.print("C ");
  Serial.print(hif);
  Serial.println("F");
}
