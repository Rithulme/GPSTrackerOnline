#include <ArduinoJson.h>
#include <WebSocketsClient.h>

//modem data
const int PIN_DTR = 25;
const int PIN_TX = 27;
const int PIN_RX = 26;
const int PWR_PIN = 4;
int mainState = 0;

//sensorIO
const int panicButtonPin = 21;
const int fuelOpenendPin = 19;
const int loadingPin = 13;
//const int clearDataButtonPin = 23;

// WebSocket client
WebSocketsClient webSocket;
bool sendTest = false;

//sensor State
bool panicState = false;
bool fuelState = false;

//leds
const int startupLEDPin = 22;
const int positionAvailableLEDPin = 32;

//gps polling
bool pollingActive = false;
bool correctPosition = false;
String received="";

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, PIN_RX, PIN_TX);

  sensorStartup();

  pinMode(startupLEDPin, OUTPUT);
  pinMode(positionAvailableLEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ManageModemState();
}
