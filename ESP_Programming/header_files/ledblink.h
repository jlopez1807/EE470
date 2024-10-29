#ifndef LEDBLINK_H
#define LEDBLINK_H

// creating a class called Blink
class Blink {
public:
    Blink(int pinNumber);      // methods
    void blinkRate(int rate);  
    void startBlinking();        

private:
    int pin;                   // member to store pin number
    int rate;                  // member to store blink rate
    void blink();         
};

#endif
