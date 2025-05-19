const String websocket_server = "161.35.217.191";
const String websocket_path = "/ws/testCommunication";
const int websocket_port = 1880;



void sendHandshake() {

  String websocketHandshake = 
    "GET " + websocket_path + " HTTP/1.1\r\n" +
    "Host: " + websocket_server + "\r\n" +
    "Upgrade: websocket\r\n" +
    "Connection: Upgrade\r\n" +
    "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n" +
    "Sec-WebSocket-Version: 13\r\n\r\n";

  Serial2.print("AT+CIPSEND\r\n");
  delay(100);
  Serial2.print(websocketHandshake);
  delay(100);
  Serial2.write(0x1A);
} 

void setupWebsocket(){


  webSocket.begin(websocket_server, websocket_port, websocket_path);
  webSocket.onEvent(onWebSocketEvent); //callback
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

String createTCPCommand(){
  return "AT+CIPSTART=\"TCP\",\"" + websocket_server + "\"," + websocket_port;
}