#include <WebSocketsClient.h>
#include <Arduino.h>
#include <WifiSetup.h>
#include <WebSocketSetup.h>
#include <globals.h>

void onWebSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected!");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected!");
      break;
    case WStype_TEXT:
      Serial.printf("WebSocket Message: %s\n", payload);
      break;
  }
}

void setupWifiAndWebsocket(){
    const char* websocket_server = "161.35.217.191";
    const char* websocket_path = "/ws/TrackerInput";
    const int websocket_port = 1880;  // wss port for secure connection
  
    connectToWiFi();
    webSocket.begin(websocket_server, websocket_port, websocket_path);
    webSocket.onEvent(onWebSocketEvent); //callback
  }

  