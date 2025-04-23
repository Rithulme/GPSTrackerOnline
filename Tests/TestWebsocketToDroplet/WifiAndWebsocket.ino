void setupWifiAndWebsocket(){
  const char* websocket_server = "161.35.217.191";
  const char* websocket_path = "/ws/testCommunication";
  const int websocket_port = 1880;  // wss port for secure connection

  connectToWiFi();
  webSocket.begin(websocket_server, websocket_port, websocket_path);
  webSocket.onEvent(onWebSocketEvent); //callback
}

void connectToWiFi() {
  const String ssid = "thosar";
  const String password = "BogVer88";

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

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