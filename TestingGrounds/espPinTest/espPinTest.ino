#include <Arduino.h>

#define firstLed 14
#define secondLed 16
#define thirdLed 25
#define fourthLed 27
#define fifthLed 13

void setup()
{
    pinMode(firstLed, OUTPUT);
    pinMode(secondLed, OUTPUT);
    pinMode(thirdLed, OUTPUT);
    pinMode(fourthLed, OUTPUT);
    pinMode(fifthLed, OUTPUT);
}

void loop()
{
    analogWrite(firstLed, 255);
    analogWrite(fourthLed, 155);
    analogWrite(thirdLed, 0);
    delay(250);
    analogWrite(secondLed, 255);
    analogWrite(fifthLed, 155);
    analogWrite(fourthLed, 0);
    delay(250);
    analogWrite(thirdLed, 255);
    analogWrite(firstLed, 155);
    analogWrite(fifthLed, 0);
    delay(250);
    analogWrite(fourthLed, 255);
    analogWrite(secondLed, 155);
    analogWrite(firstLed, 0);
    delay(250);
    analogWrite(fifthLed, 255);
    analogWrite(thirdLed, 155);
    analogWrite(secondLed, 0);
    delay(250);
}