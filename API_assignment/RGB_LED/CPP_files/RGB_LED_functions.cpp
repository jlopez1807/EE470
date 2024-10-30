#include "RGB_LED.h"

// Function to control the RGB
void controlRgbLed() {
    HTTPClient https;
    WiFiClientSecure client;  
    client.setInsecure();  // Allow insecure SSL connection 
    https.begin(client, rgbUrl);  
    // Get request and obtaining response code
    int httpCode = https.GET();
    Serial.print("HTTP Response Code for RGB: ");
    Serial.println(httpCode);
    // Get request successfull
    if (httpCode > 0) {
        String payload = https.getString();
        Serial.println(payload);
    // Reads values for each color
        int red = 0, green = 0, blue = 0;
        sscanf(payload.c_str(), "Red: %d\nGreen: %d\nBlue: %d", &red, &green, &blue);
    // Sends value to RGB to display a hue
        analogWrite(redPin, red);   
        analogWrite(greenPin, green); 
        analogWrite(bluePin, blue); 

        Serial.printf("RGB values - Red: %d, Green: %d, Blue: %d\n", red, green, blue);
    // Get request not successfull
    } else {
        Serial.println("Error on HTTP request for RGB values");
    }
    https.end();
}
