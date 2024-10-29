#include "ledblink.h"
#include <Arduino.h>

Blink LED(4);  // Using GPIO 4 or D2

void setup() {
    LED.blinkRate(500);   // blink rate is 500 milliseconds
    LED.startBlinking();  // blinking the LED
}

void loop() {
}
