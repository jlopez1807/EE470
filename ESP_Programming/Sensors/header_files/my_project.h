#ifndef MY_PROJECT_H
#define MY_PROJECT_H

// Adding libraries to the project
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // Include the ArduinoJson library
#include "wifi_cred3.h"  // Use the credentials stored in Wi-Fi file

// Defining sensor pin and type
#define DHT_PIN 2  // Pin for the DHT11 sensor (Temperature + Humidity) (D4)
#define BUTTON_PIN 4 // Pushbutton pin (D2)

// Defining the DHT sensor type (for DHT11)
#define DHT_TYPE DHT11  

// Timeout for Wi-Fi connection (in milliseconds)
const unsigned long connectTimeoutMs = 30000;  // Timeout for 30 seconds

// My website/database URL
extern String url;

// Custom timeout (in milliseconds)
const unsigned long maxTimeout = 65500;  // Set to 65.5 seconds (maximum supported timeout by the library)
const unsigned int maxRetries = 3;  // Limit retries to 3 attempts

// DHT sensor initialization
extern DHT dht;

// Function declarations
void transmitData(float temperature, float humidity);

#endif  // MY_PROJECT_H
