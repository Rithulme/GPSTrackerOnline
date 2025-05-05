#include <WiFi.h>
#include <Arduino.h>
#include "WifiSetup.h"

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