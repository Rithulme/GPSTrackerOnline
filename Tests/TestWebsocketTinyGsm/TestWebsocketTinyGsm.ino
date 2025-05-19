#define TINY_GSM_MODEM_SIM7000
#include <TinyGsmClient.h>
#include <WebSocketsClient.h>

// Your modem instance
TinyGsm modem(Serial2);
TinyGsmClient client(modem);
WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200); // SIM7000G default

  // Start modem
  modem.restart();

  // Connect to network
  modem.gprsConnect("internet.proximus.be");

  // Wait for GPRS to connect
  while (!modem.isGprsConnected()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("GPRS connected.");

  // ✅ Pass the TinyGSM client, NOT default WiFiClient
  webSocket.begin(client, "161.35.217.191", 1880, "/ws/testCommunication");

  // Optional config
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();  // This is safe now
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  // Handle messages, connection, etc.
}