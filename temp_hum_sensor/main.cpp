/*
 * ----------------------------------------------
 * Project/Program Name : Sending a Request V3
 * File Name            : main.cpp
 * Author               : Jessie Lopez
 * Date                 : 19/10/2024
 * Version              : 1
 * 
 * Purpose:
 *    The purpose of this program is to take readings from a temperature and humidity sensor when a button is pressed and send the data to my web server/database.
 * 
 * Inputs:
 *    - DHT sensor (connected to DHT_PIN, pin 2)
 *    - Pushbutton (connected to BUTTON_PIN, pin 4)
 *    - Wi-Fi credentials (WIFI_SSID and WIFI_PASSWORD)
 * 
 * Outputs:
 *    - Serial output for debugging and logging data.
 *    - HTTP request to a remote server with sensor data (temperature and humidity).
 * 
 * Example Application:
 *    This program reads temperature and humidity data from the DHT11 sensor when the pushbutton is pressed,
 *    and sends the data to a remote web server for storage.
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
 *    - 1st pin of sensor is data pin (goes to D4), 2nd pin is Vcc, 3rd pin is ground. 
 *    - WiFi credentials needs to be stored/changed in wifi_cred3.h file. 
 *    - This program does not take time into consideration currently
 * -----
 */
#include "my_project.h"

// Setup function
void setup() {
    // Start the serial communication
    Serial.begin(115200);
    Serial.println("Initializing...");

    // Initialize the pushbutton pin
    pinMode(BUTTON_PIN, INPUT_PULLUP);

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

    // Initialize DHT sensor
    dht.begin();  // Start DHT sensor (Temperature + Humidity)
}

// Main loop function
void loop() {
    // Check if the button is pressed (active LOW)
    if (digitalRead(BUTTON_PIN) == LOW) {
        // Read temperature from the sensor
        float temperature = dht.readTemperature();

        // Read humidity from the sensor
        float humidity = dht.readHumidity();

        // Check if the sensor readings are valid
        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from the sensor.");
        } else {
            // Print the data to Serial Monitor
            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.print(" °C  Humidity: ");
            Serial.print(humidity);
            Serial.println(" %");

            // Send the data to your database
            transmitData(temperature, humidity);
        }

        delay(1000);  // Debounce the button press
    }

    delay(500);  // Short delay to avoid bouncing issues and reduce serial print load
}
