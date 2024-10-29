#ifndef REMOTE_LED_H
#define REMOTE_LED_H

// Adding libraries to the project
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "wifi_cred.h"

// Timeout for Wi-Fi connection (in milliseconds)
const unsigned long connectTimeoutMs = 30000;  // Timeout for 30 seconds

#endif  // REMOTE_LED_H
