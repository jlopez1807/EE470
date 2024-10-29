#include "ledblink.h"
#include <Arduino.h>  

// Constructor: Initializes the pin number and sets the default blink rate
Blink::Blink(int pinNumber) {
    pin = pinNumber;           
    pinMode(pin, OUTPUT);      
    rate = 1000;               // Default blink rate of 1000 milliseconds (1 second)
}

// Method to set the blink rate (in milliseconds)
void Blink::blinkRate(int rate) {
    this->rate = rate;  // Set the rate
}

// Private method to blink the LED
void Blink::blink() {
    digitalWrite(pin, HIGH);   // Turn LED on
    delay(rate / 2);           // Wait for half the blink rate
    digitalWrite(pin, LOW);    // Turn LED off
    delay(rate / 2);           // Wait for the other half
}

// Method to start blinking the LED
void Blink::startBlinking() {
    while (true) {
        blink();  // Continuously blink the LED
    }
}
