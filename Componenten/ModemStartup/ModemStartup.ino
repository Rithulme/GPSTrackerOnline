#include <ArduinoJson.h>

//modem data
const int PIN_DTR = 25;
const int PIN_TX = 27;
const int PIN_RX = 26;
const int PWR_PIN = 4;
int mainState = 0;

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

  pinMode(startupLEDPin, OUTPUT);
  pinMode(positionAvailableLEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ManageModemState();
}
