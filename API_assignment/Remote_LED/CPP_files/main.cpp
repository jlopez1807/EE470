/*
 * ----------------------------------------------
 * Project/Program Name : Sensor_API_Dashboard
 * File Name            : main.cpp
 * Author               : Jessie Lopez
 * Date                 : 27/10/2024
 * Version              : 1
 * 
 * Purpose:
 *    The purpose of this program is to turn an LED on and off remotely. The form data can be accessed via https://ssu.jessielopez.net/PHP_Projects/remote_led.html
 * 
 * Inputs:
 *    - Form data for on or off on webpage
 * Outputs:
 *    - LED_BUILTIN
 * Dependencies:
 *    - ESP8266WiFi library
 *    - ESP8266HTTPClient library
 *    - Arduino library
 *    - WiFiClientSecure library
 * 
 * Usage Notes:
 *    - This program will only check the txt file every two minutes. Any changes between that time may not be taken into account. 
 * -----
 */

#include "remote_led.h"

// URL to access txt file to get form results
String serverUrl = "https://ssu.jessielopez.net/PHP_Projects/results.txt"; 

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as an output
    // Start the serial communication
    Serial.begin(115200);
    Serial.println("Initializing...");

    // Connect to Wi-Fi (wifi credentials stored in other file for security)
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long startAttemptTime = millis();

    // Wait for Wi-Fi to connect
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startAttemptTime >= connectTimeoutMs) {
            Serial.println("Failed to connect to Wi-Fi.");
            return;
        }
        Serial.print("...");
        delay(1000);  // Wait for 1 second before checking again
    }

    // Print the local IP address once connected
    Serial.print("Connected to Wi-Fi, IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Request LED state
    HTTPClient https;
    WiFiClientSecure client;  
    client.setInsecure();  // Allow insecure SSL connection 
    https.begin(client, serverUrl);  

    int httpCode = https.GET();
    Serial.print("HTTP Response Code: "); // Debugging line
    Serial.println(httpCode); // Print the HTTP status code

    if (httpCode > 0) {
        String payload = https.getString();
        Serial.println(payload);

        if (payload == "ON") {
            digitalWrite(LED_BUILTIN, LOW);
            Serial.println("Led is on");
        } else {
            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("Led is off");
        }
    } else {
        Serial.println("Error on HTTP request");
    }
    https.end();

    delay(120000); // Check every 2 minutes
}
