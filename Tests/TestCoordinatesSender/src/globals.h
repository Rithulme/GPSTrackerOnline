#ifndef GLOBALS_H
#define GLOBALS_H

#include <PubSubClient.h>
#include <WiFi.h>

extern WiFiClient espClient;
extern PubSubClient client;
extern IPAddress mqtt_server;
extern String clientId;

#endif
