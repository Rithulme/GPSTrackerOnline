#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <Arduino.h>
#include <WebSocketsClient.h>

void setupWifiAndMQTT();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

#endif