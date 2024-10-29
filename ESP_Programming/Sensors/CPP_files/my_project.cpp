#include "my_project.h"

// My website/database url
String url = "https://ssu.jessielopez.net/PHP_Projects/Project2V2.php";

// DHT sensor initialization
DHT dht(DHT_PIN, DHT_TYPE);  // DHT sensor for temperature and humidity

unsigned long startMillis = millis();  // Record the start time

// Function to obtain current time
void fetchCurrentTime(String &mytime) {
    // Initialize HTTPClient
    HTTPClient httpsTime;
    String timeUrl;
    // API endpoint for the current time
    // Read user input from the serial monitor
     while (timeUrl.isEmpty()) {
        Serial.println("Enter time zone (1-6, default - Los Angeles):");
        delay(5000);
        String input = Serial.readStringUntil('\n'); // Read until newline
        int userInput = input.toInt(); // Convert input string to integer    
    // Set the timezone based on user input
        switch (userInput) {
            case 1:
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/New_York"; // Eastern Time
                Serial.println("Time zone selected: Eastern Time");
                break;
            case 2:
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/Chicago"; // Central Time
                Serial.println("Time zone selected: Central Time");
                break;
            case 3:
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/Denver"; // Mountain Time
                Serial.println("Time zone selected: Mountain Time");
                break;
            case 4:
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles"; // Pacific Time
                Serial.println("Time zone selected: Pacific Time");
                break;
            case 5:
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/Anchorage"; // Alaska Time
                Serial.println("Time zone selected: Alaska Time");
                break;
            case 6:
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/Adak"; // Hawaii-Aleutian Time
                Serial.println("Time zone selected: Hawaii-Aleutian Time");
                break;
            default:
                Serial.println("Not a valid input. Default time zone is set to Los Angeles.");
                timeUrl = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles"; // Pacific Time
                break; 
        }
     }
    // Initialize WiFiClient object for the HTTP request
    WiFiClientSecure client;
    client.setInsecure();  // Allow insecure SSL connection 

    // Send the GET request
    if (httpsTime.begin(client, timeUrl)) {  
        int httpCode = httpsTime.GET();
        // Successful request
        if (httpCode > 0) {
            String payload = httpsTime.getString();  // Get the server response
           // Serial.println("Time API Response: " + payload);  // Print the response payload
            // Parse the JSON response
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);

            // Extract dateTime and store it in mytime
            if (!error) {
                mytime = doc["dateTime"].as<String>();
                Serial.println("Current Time: " + mytime);
            } else {
                Serial.println("Failed to parse JSON: " + String(error.c_str()));
            }
        // failed request
        } else {
            Serial.println("Failed to fetch time: " + String(httpCode));
        }
        httpsTime.end();  // Close the HTTP connection
    // Couldnt connect
    } else {
        Serial.printf("[HTTPS] Unable to connect to %s\n", timeUrl.c_str());
    }
}
// Function to send data to database/webpage
void transmitData(float temperature, float humidity) {
    String mytime;
    fetchCurrentTime(mytime);  // Fetch current time
    // Initialize HTTPClient
    HTTPClient https;

    // Construct the server URL with query parameters
    String data1 = "?nodeId=node-1&nodeTemp=";
    String data3 = "&nodeHum=" + String(humidity);
    String data4 = "&time_received=" + mytime;  // Use the fetched time
    String fullUrl = url + data1 + String(temperature) + data3 + data4;

    // Initialize WiFiClient object for the HTTP request
    WiFiClientSecure client;
    client.setInsecure();  // Allow insecure SSL connection 

    unsigned int retryCount = 0;  // Track number of retries

    // Send data to the server with retry logic
    while (retryCount < maxRetries) {
        if (https.begin(client, fullUrl)) {  

            // Send the GET request
            int httpCode = https.GET();
            // Successful request
            if (httpCode > 0) {
                String payload = https.getString();  // Get the server response
                Serial.println("Response code: " + String(httpCode));
             //   Serial.println("Response payload: " + payload);  // Print the response payload
                break;  // Exit the loop if request is successful
            } else {    // Request failed
                Serial.println("Request failed, retrying...");
                retryCount++;  // Increment retry counter
                delay(1000);  // Retry after 1 second
            }
            https.end();  // Close the HTTP connection
        } else {          // Connection error
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
