#include <FastLED.h>

// Defining Global Immutable Variables
#define NUM_LEDS 150
#define DATA_ONE 8
#define DATA_TWO 9
#define DATA_THREE 10
#define DATA_FOUR 11
#define DATA_FIVE 12
#define BRIGHTNESS 90
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000

// Threshold for Distance Sensor
#define THRESHOLD 50

// Sensor Pin Designations
const int ECHO_PIN = 2;
const int TRIGGER_PIN = 3;

// Declaring arrays
CRGB leds[NUM_LEDS];
CRGB secondLeds[NUM_LEDS];
CRGB thirdLeds[NUM_LEDS];
CRGB fourthLeds[NUM_LEDS];
CRGB fifthLeds[NUM_LEDS];

// Distance variable for spacing
int delayDistance = 1;

// Head Variables
// These will be some of the main differences in this code
int headBlue = 0;
int headRed = -30;
int headGreen = -50;
int headYellow = -100;
int headWhite = -70;

int secondHeadBlue = -10;
int secondHeadRed = -40;
int secondHeadGreen = -60;
int secondHeadYellow = -80;
int secondHeadWhite = -110;
