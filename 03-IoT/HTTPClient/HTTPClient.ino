#include <SPI.h>
#include <HttpClient.h>
#include <Ethernet.h>
#include <EthernetClient.h>

// String contendo o campo HOST da URL
String host = "te2023-iot-038082f8e478.herokuapp.com";
// String contendo o campo PATH da URL
String path = "/";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

void setup() {
  Serial.begin(9600); 

  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }  
}

void loop() {
  int err = 0;

  EthernetClient c;
  HttpClient http(c);
  
  err = http.get(host.c_str(), path.c_str()); // Dispara a requisição HTTP GET para a URL http://{host}{path}

  if (err == 0)
  {
    Serial.println("startedRequest ok");

    int statusCode = http.responseStatusCode();  // Acessando o código de status da requisição HTTP
    if (statusCode >= 0)
    {
      Serial.print("Status code: ");
      Serial.println(statusCode); 

      err = http.skipResponseHeaders();
      if (err >= 0)
      { 
        String body = getResponseBody(http); // Acessando o corpo da resposta HTTP (função definida ao final do arquivo)
        Serial.print("Body: ");
        Serial.println(body);
      }
      else
      {
        Serial.print("Failed to skip response headers: ");
        Serial.println(err);
      }
    }
    else
    {    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();

  // And just stop, now that we've tried a download
  while(1);

}

String getResponseBody(HttpClient http) {
  int bodyLen = http.contentLength();
  unsigned long timeoutStart = millis();
  char c;
  String responseBody = "";

  while ( (http.connected() || http.available()) && ((millis() - timeoutStart) < kNetworkTimeout) ) {
      if (http.available()) {
          c = http.read();
          responseBody += c;
          bodyLen--;
          timeoutStart = millis();
      }
      else {
          delay(kNetworkDelay);
      }
  }
  return responseBody;
}
