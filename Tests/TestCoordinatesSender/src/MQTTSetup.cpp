#include <WebSocketsClient.h>
#include <Arduino.h>
#include <WifiSetup.h>
#include <MQTTSetup.h>
#include <globals.h>

void callback(char* topic, byte* payload, unsigned int length) {
  String message;

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message: ");
  Serial.println(message); 
  
}

void setupWifiAndMQTT(){

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);  
    connectToWiFi();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

  