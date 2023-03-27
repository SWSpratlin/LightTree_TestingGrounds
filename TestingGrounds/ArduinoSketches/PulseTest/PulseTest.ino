#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Pin and LED count for the one strip I have
#define LED_PIN 10
#define LED_COUNT 150