/*
 * ----------------------------------------------
 * Project/Program Name : RGB_LED
 * File Name            : main.cpp
 * Author               : Jessie Lopez
 * Date                 : 29/10/2024
 * Version              : 1
 * 
 * Purpose:
 *    The purpose of this program is to control an RGB LED via sliders on https://ssu.jessielopez.net/PHP_Projects/RGB_LED.php
 * 
 * Inputs:
 *    - Wi-Fi credentials (WIFI_SSID and WIFI_PASSWORD)
 * 
 * Outputs:
 *    - RBG LED light
 * 
 * Dependencies:
 *    - Adafruit sensor library
 *    - ESP8266WiFi library
 *    - ESP8266HTTPClient library
 *    - Arduino library
 *    - WiFiClientSecure library
 *    - DHT library
 * 
 * Usage Notes:
 *    - D1 goes to 1kohm resistor then to 1st pin of RGB (red), 2nd pin goes to ground, D5 goes to 1kohm then to 3rd pin (green), D6 goes to 1kohm resistor then
 *      to 4th pin of RGB (blue)
 * -----
 */
// Adding header file
#include "RGB_LED.h"

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as an output
    pinMode(redPin, OUTPUT);       // Set RGB pins as outputs
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    // Set RGB pins to LOW to ensure they are off initially
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    
    Serial.begin(115200);
    Serial.println("Initializing...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startAttemptTime >= connectTimeoutMs) {
            Serial.println("Failed to connect to Wi-Fi.");
            return;
        }
        Serial.print("...");
        delay(1000);  // Wait for 1 second before checking again
    }

    Serial.print("Connected to Wi-Fi, IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {

    // Control RGB LED
    controlRgbLed();
    delay(20000); // Check every 20 seconds
}

