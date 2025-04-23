#include <WebSocketsClient.h>

//modem data
const int PIN_DTR = 25;
const int PIN_TX = 27;
const int PIN_RX = 26;
const int PWR_PIN = 4;

const int startupLEDPin = 22;

int mainState = 0;
bool sendTest = false;

// WebSocket client
WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 26, 27);

  pinMode(startupLEDPin, OUTPUT);
}

void loop() {
  ManageModemState();

}
