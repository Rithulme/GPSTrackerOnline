#include <PubSubClient.h>
#include <WiFi.h>
#include <Arduino.h>
#include <MQTTSetup.h>
#include "globals.h"

String generateClientID() {
  // Generate a unique client ID based on the ESP32's MAC address
  uint8_t mac[6];
  WiFi.macAddress(mac);
  String macString = "ESP32_";
  for (int i = 0; i < 6; i++) {
    if (mac[i] < 16) macString += "0"; // Add leading zero if needed
    macString += String(mac[i], HEX);
  }
  macString.toUpperCase();
  return macString;
}

String data = "{\"Type\":\"coordinates\",\"lon\":4.056676,\"lat\":51.02624,\"speed\":32.6}-{\"Type\":\"coordinates\",\"lon\":4.056946,\"lat\":51.02582,\"speed\":13.33}-{\"Type\":\"coordinates\",\"lon\":4.055083,\"lat\":51.02497,\"speed\":49.82}-{\"Type\":\"coordinates\",\"lon\":4.052234,\"lat\":51.0238,\"speed\":62.23}-{\"Type\":\"coordinates\",\"lon\":4.049216,\"lat\":51.02256,\"speed\":62.41}-{\"Type\":\"coordinates\",\"lon\":4.046085,\"lat\":51.02131,\"speed\":62.04}-{\"Type\":\"coordinates\",\"lon\":4.043365,\"lat\":51.01988,\"speed\":61.67}-{\"Type\":\"coordinates\",\"lon\":4.040905,\"lat\":51.0181,\"speed\":63.34}-{\"Type\":\"coordinates\",\"lon\":4.038311,\"lat\":51.01624,\"speed\":68.15}-{\"Type\":\"coordinates\",\"lon\":4.035461,\"lat\":51.01442,\"speed\":68.34}-{\"Type\":\"coordinates\",\"lon\":4.032194,\"lat\":51.01294,\"speed\":65.93}-{\"Type\":\"coordinates\",\"lon\":4.028841,\"lat\":51.01158,\"speed\":64.63}-{\"Type\":\"coordinates\",\"lon\":4.025652,\"lat\":51.01021,\"speed\":63.89}-{\"Type\":\"coordinates\",\"lon\":4.022979,\"lat\":51.00871,\"speed\":56.49}-{\"Type\":\"coordinates\",\"lon\":4.020592,\"lat\":51.0074,\"speed\":51.86}-{\"Type\":\"coordinates\",\"lon\":4.018265,\"lat\":51.0062,\"speed\":48.71}-{\"Type\":\"coordinates\",\"lon\":4.015982,\"lat\":51.00536,\"speed\":41.3}-{\"Type\":\"coordinates\",\"lon\":4.014867,\"lat\":51.00496,\"speed\":17.41}-{\"Type\":\"coordinates\",\"lon\":4.013834,\"lat\":51.00461,\"speed\":20}-{\"Type\":\"coordinates\",\"lon\":4.01359,\"lat\":51.00455,\"speed\":0}-{\"Type\":\"coordinates\",\"lon\":4.013106,\"lat\":51.00434,\"speed\":19.82}-{\"Type\":\"coordinates\",\"lon\":4.012093,\"lat\":51.00553,\"speed\":42.6}-{\"Type\":\"coordinates\",\"lon\":4.010561,\"lat\":51.00708,\"speed\":53.89}-{\"Type\":\"coordinates\",\"lon\":4.008898,\"lat\":51.00877,\"speed\":53.34}-{\"Type\":\"coordinates\",\"lon\":4.007298,\"lat\":51.01028,\"speed\":47.23}-{\"Type\":\"coordinates\",\"lon\":4.006145,\"lat\":51.01184,\"speed\":45}-{\"Type\":\"coordinates\",\"lon\":4.005134,\"lat\":51.01336,\"speed\":47.23}-{\"Type\":\"coordinates\",\"lon\":4.005411,\"lat\":51.01475,\"speed\":44.45}-{\"Type\":\"coordinates\",\"lon\":4.005768,\"lat\":51.01649,\"speed\":48.15}-{\"Type\":\"coordinates\",\"lon\":4.006081,\"lat\":51.01821,\"speed\":45.56}-{\"Type\":\"coordinates\",\"lon\":4.006417,\"lat\":51.01987,\"speed\":43.71}-{\"Type\":\"coordinates\",\"lon\":4.00572,\"lat\":51.02141,\"speed\":44.63}-{\"Type\":\"coordinates\",\"lon\":4.00413,\"lat\":51.02269,\"speed\":41.67}-{\"Type\":\"coordinates\",\"lon\":4.00345,\"lat\":51.02408,\"speed\":37.41}-{\"Type\":\"coordinates\",\"lon\":4.003716,\"lat\":51.02522,\"speed\":32.78}-{\"Type\":\"coordinates\",\"lon\":4.002375,\"lat\":51.02541,\"speed\":22.22}-{\"Type\":\"coordinates\",\"lon\":4.001821,\"lat\":51.02641,\"speed\":31.11}-{\"Type\":\"coordinates\",\"lon\":4.000402,\"lat\":51.02745,\"speed\":36.85}-{\"Type\":\"coordinates\",\"lon\":3.998959,\"lat\":51.02816,\"speed\":30}-{\"Type\":\"coordinates\",\"lon\":3.997183,\"lat\":51.02849,\"speed\":35.93}-{\"Type\":\"coordinates\",\"lon\":3.994825,\"lat\":51.0288,\"speed\":40.74}-{\"Type\":\"coordinates\",\"lon\":3.992444,\"lat\":51.02914,\"speed\":42.23}-{\"Type\":\"coordinates\",\"lon\":3.990015,\"lat\":51.02955,\"speed\":41.86}-{\"Type\":\"coordinates\",\"lon\":3.98807,\"lat\":51.03048,\"speed\":40.56}-{\"Type\":\"coordinates\",\"lon\":3.98636,\"lat\":51.0317,\"speed\":43.52}-{\"Type\":\"coordinates\",\"lon\":3.984769,\"lat\":51.03291,\"speed\":41.67}-{\"Type\":\"coordinates\",\"lon\":3.983388,\"lat\":51.03419,\"speed\":41.11}-{\"Type\":\"coordinates\",\"lon\":3.982814,\"lat\":51.03566,\"speed\":39.82}-{\"Type\":\"coordinates\",\"lon\":3.982338,\"lat\":51.03706,\"speed\":39.08}-{\"Type\":\"coordinates\",\"lon\":3.981983,\"lat\":51.04005,\"speed\":36.48}-{\"Type\":\"coordinates\",\"lon\":3.982829,\"lat\":51.04124,\"speed\":32.22}-{\"Type\":\"coordinates\",\"lon\":3.98395,\"lat\":51.04205,\"speed\":22.96}-{\"Type\":\"coordinates\",\"lon\":3.98409,\"lat\":51.0429,\"speed\":31.11}-{\"Type\":\"coordinates\",\"lon\":3.982992,\"lat\":51.04406,\"speed\":38.89}-{\"Type\":\"coordinates\",\"lon\":3.981834,\"lat\":51.04541,\"speed\":38.52}-{\"Type\":\"coordinates\",\"lon\":3.981031,\"lat\":51.04687,\"speed\":43.15}-{\"Type\":\"coordinates\",\"lon\":3.978948,\"lat\":51.04784,\"speed\":44.26}-{\"Type\":\"coordinates\",\"lon\":3.976842,\"lat\":51.04875,\"speed\":44.82}-{\"Type\":\"coordinates\",\"lon\":3.975357,\"lat\":51.04998,\"speed\":36.67}-{\"Type\":\"coordinates\",\"lon\":3.974801,\"lat\":51.05045,\"speed\":11.48}-{\"Type\":\"coordinates\",\"lon\":3.974295,\"lat\":51.05049,\"speed\":25.56}-{\"Type\":\"coordinates\",\"lon\":3.971826,\"lat\":51.04945,\"speed\":65.18999}-{\"Type\":\"coordinates\",\"lon\":3.964881,\"lat\":51.04699,\"speed\":64.63}-{\"Type\":\"coordinates\",\"lon\":3.961204,\"lat\":51.04687,\"speed\":55.19}-{\"Type\":\"coordinates\",\"lon\":3.958292,\"lat\":51.04736,\"speed\":47.23}-{\"Type\":\"coordinates\",\"lon\":3.95732,\"lat\":51.04727,\"speed\":0}-{\"Type\":\"coordinates\",\"lon\":3.957327,\"lat\":51.04727,\"speed\":0}-{\"Type\":\"coordinates\",\"lon\":3.956896,\"lat\":51.04721,\"speed\":17.78}-{\"Type\":\"coordinates\",\"lon\":3.954862,\"lat\":51.04696,\"speed\":38.52}-{\"Type\":\"coordinates\",\"lon\":3.952671,\"lat\":51.04688,\"speed\":36.85}-{\"Type\":\"coordinates\",\"lon\":3.950424,\"lat\":51.04699,\"speed\":37.41}-{\"Type\":\"coordinates\",\"lon\":3.948138,\"lat\":51.04685,\"speed\":36.67}-{\"Type\":\"coordinates\",\"lon\":3.946826,\"lat\":51.04667,\"speed\":19.82}-{\"Type\":\"coordinates\",\"lon\":3.946609,\"lat\":51.04803,\"speed\":41.3}-{\"Type\":\"coordinates\",\"lon\":3.946482,\"lat\":51.04945,\"speed\":34.82}-{\"Type\":\"coordinates\",\"lon\":3.94718,\"lat\":51.05098,\"speed\":46.67}-{\"Type\":\"coordinates\",\"lon\":3.947936,\"lat\":51.05269,\"speed\":50}-{\"Type\":\"coordinates\",\"lon\":3.948095,\"lat\":51.05478,\"speed\":65.93}-{\"Type\":\"coordinates\",\"lon\":3.948295,\"lat\":51.0573,\"speed\":68.15}-{\"Type\":\"coordinates\",\"lon\":3.948265,\"lat\":51.05989,\"speed\":68.71}-{\"Type\":\"coordinates\",\"lon\":3.947689,\"lat\":51.06243,\"speed\":68.34}-{\"Type\":\"coordinates\",\"lon\":3.947142,\"lat\":51.06499,\"speed\":68.34}-{\"Type\":\"coordinates\",\"lon\":3.946757,\"lat\":51.06751,\"speed\":68.34}-{\"Type\":\"coordinates\",\"lon\":3.94689,\"lat\":51.06992,\"speed\":56.67}-{\"Type\":\"coordinates\",\"lon\":3.946997,\"lat\":51.07185,\"speed\":49.63}-{\"Type\":\"coordinates\",\"lon\":3.947101,\"lat\":51.07377,\"speed\":51.67}-{\"Type\":\"coordinates\",\"lon\":3.947225,\"lat\":51.07572,\"speed\":53.71}-{\"Type\":\"coordinates\",\"lon\":3.947371,\"lat\":51.07798,\"speed\":62.97}-{\"Type\":\"coordinates\",\"lon\":3.948098,\"lat\":51.08024,\"speed\":63.89}-{\"Type\":\"coordinates\",\"lon\":3.95036,\"lat\":51.08205,\"speed\":59.26}-{\"Type\":\"coordinates\",\"lon\":3.951493,\"lat\":51.08323,\"speed\":3.89}-{\"Type\":\"coordinates\",\"lon\":3.949758,\"lat\":51.08369,\"speed\":55.75}-{\"Type\":\"coordinates\",\"lon\":3.94644,\"lat\":51.08406,\"speed\":58.71}-{\"Type\":\"coordinates\",\"lon\":3.942819,\"lat\":51.08407,\"speed\":63.34}-{\"Type\":\"coordinates\",\"lon\":3.939052,\"lat\":51.08426,\"speed\":62.41}-{\"Type\":\"coordinates\",\"lon\":3.935589,\"lat\":51.08472,\"speed\":57.78}-{\"Type\":\"coordinates\",\"lon\":3.932203,\"lat\":51.0849,\"speed\":62.41}-{\"Type\":\"coordinates\",\"lon\":3.928316,\"lat\":51.08486,\"speed\":65.38}-{\"Type\":\"coordinates\",\"lon\":3.924435,\"lat\":51.08483,\"speed\":66.49}-{\"Type\":\"coordinates\",\"lon\":3.920677,\"lat\":51.08482,\"speed\":57.6}-";
String tempString = data;
String clientId = generateClientID();
WiFiClient espClient;
PubSubClient client(espClient);
IPAddress mqtt_server(161, 35, 217, 191);
const char* MQTT_path = "TrackerInput";   

void setup() {
    Serial.begin(115200);
    setupWifiAndMQTT();
    reconnect();
    delay(3000);
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); 
}

void loop() {
    client.loop();

    if (tempString.indexOf('-') > -1 && millis() > 15000)
    {
        delay(5000);
        Serial.println("Sending data to WebSocket server...");
        String currentData = tempString.substring(0, tempString.indexOf('-'));
        tempString = tempString.substring(tempString.indexOf('-') + 1);

        if (client.publish(MQTT_path, currentData.c_str())) {
            Serial.println("Publish to mobile succeeded");   
        }

    }
}



