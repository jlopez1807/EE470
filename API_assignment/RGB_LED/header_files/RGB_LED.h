#ifndef RGB_LED_H
#define RGB_LED_H

// Adding libraries to the project
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "wifi_cred.h"

extern String rgbUrl;
const unsigned long connectTimeoutMs = 30000;  // Timeout for 30 seconds

// RGB LED pin configuration
const int redPin = D1;   // Change as needed
const int greenPin = D5; // Change as needed
const int bluePin = D6;  // Change as needed

// Function prototypes
void controlRgbLed();

#endif  // RGB_LED_H
