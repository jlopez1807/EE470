#include "my_project.h"

// My website/database url
String url = "https://ssu.jessielopez.net/PHP_Projects/Project2.php";

// DHT sensor initialization
DHT dht(DHT_PIN, DHT_TYPE);  // DHT sensor for temperature and humidity

unsigned long startMillis = millis();  // Record the start time

void transmitData(float temperature, float humidity) {
    // Initialize HTTPClient
    HTTPClient https;

    // Construct the server URL with query parameters
    String data1 = "?nodeId=node-1&nodeTemp=";
    String data3 = "&nodeHum=" + String(humidity);
    String fullUrl = url + data1 + String(temperature) + data3;

    // Initialize WiFiClient object for the HTTP request
    WiFiClientSecure client;
    client.setInsecure();  // Allow insecure SSL connection 

    unsigned int retryCount = 0;  // Track number of retries

    // Send data to the server with retry logic
    while (retryCount < maxRetries) {
        if (https.begin(client, fullUrl)) {  

            // Send the GET request
            int httpCode = https.GET();
            if (httpCode > 0) {
                // Successful request
                String payload = https.getString();  // Get the server response
                Serial.println("Response code: " + String(httpCode));
                Serial.println("Response payload: " + payload);  // Print the response payload
                break;  // Exit the loop if request is successful
            } else {
                // Request failed
                Serial.println("Request failed, retrying...");
                retryCount++;  // Increment retry counter
                delay(1000);  // Retry after 1 second
            }

            https.end();  // Close the HTTP connection
        } else {
            // Connection error
            Serial.printf("[HTTPS] Unable to connect to %s\n", fullUrl.c_str());
            break;  // Exit if unable to connect
        }

        // Check if the custom timeout was reached
        if (millis() - startMillis >= maxTimeout) {
            Serial.println("Request timed out after " + String(maxTimeout / 1000) + " seconds");
            break;  // Exit loop after reaching the maxTimeout
        }
    }

    // If retries exceed the limit, log failure
    if (retryCount == maxRetries) {
        Serial.println("Failed after " + String(maxRetries) + " retries.");
    }
}
