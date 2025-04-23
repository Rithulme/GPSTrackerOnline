#include <WiFi.h>
#include <WebSocketsClient.h>

// WebSocket client
WebSocketsClient webSocket;
bool sendingDone = false;

void setup() {
  Serial.begin(115200);
      
  //setting up wifi and websocket  
  delay(3000);
  setupWifiAndWebsocket();
  delay(3000);
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() { 
  webSocket.loop();

  if (millis() > 15000) {
    delay(3000);
    Serial.println("start sending");
    String message = "Hello websocket";
    webSocket.sendTXT(message);
  }

  
}
