#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <Arduino.h>
#include <WebSocketsClient.h>

void setupWifiAndWebsocket();
void onWebSocketEvent(WStype_t type, uint8_t * payload, size_t length);

#endif