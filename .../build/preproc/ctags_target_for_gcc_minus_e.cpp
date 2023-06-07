# 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
# 2 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 2

// Defining Global Immutable Variables
# 16 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
// Threshold for Distance Sensor


// Sensor Pin Designations
const int ECHO_PIN = 2;
const int TRIGGER_PIN = 3;

// Declaring arrays
CRGB leds[150];
CRGB secondLeds[150];
CRGB thirdLeds[150];
CRGB fourthLeds[150];
CRGB fifthLeds[150];

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

int thirdHeadBlue = -5;
int thirdHeadRed = -25;
int thirdHeadGreen = -35;
int thirdHeadYellow = -55;
int thirdHeadWhite - -75;

// Color variables (need to be global for them to change consistently)
int pulseColorRed = 250;
int pulseColorBlue = 150;
int pulseColorYellow = 30;
int pulseColorGreen = 100;
int pulseColorWhite = 0;

void setup()
{
    // PinModes for US Sensor
    pinMode(TRIGGER_PIN, 0x1);
    pintMode(ECHO_PIN, 0x0);

    // Setup the LED strips
    FastLED.setMaxPowerInMilliWatts(5, 3000);

    // Set up pins for LED arrays.
    // Important to note that I'll be setting
    // up the pins rather than strips. I have 5 total
    // possibilities
    FastLED.addLeds<WS2812B, 8, GRB>(leds, 150);
    FastLED.addLeds<WS2812B, 9, GRB>(secondLeds, 150);
    FastLED.addLeds<WS2812B, 10, GRB>(thirdLeds, 150);

    // Set global brightness value
    FastLED.setBrightness(90);

    // Show the first Instances of the LEDs
    FastLED.show();

    // startup Delay to give things some breathing room
    delay(500);
    Serial.begin(9600);
}

void loop()
{
    // update pulse distance
    measureDist(delayDistance);

    // call first red pulse
    pulse(leds, 150, pulseColorRed, headRed, 0);

    // call the first blue pulse
    pulse(leds, 150, pulseColorBlue, headBlue, 10);

    // call the first yellow pulse
    pulse(leds, 150, pulseColorYellow, headYellow, 20);

    // call the first green pulse
    pulse(leds, 150, pulseColorGreen, headGreen, 30);

    // call the second red pulse
    pulse(secondLeds, 150, pulseColorRed, secondHeadRed, 20);

    // call the second blue pulse
    pulse(secondLeds, 150, pulseColorBlue, secondHeadBlue, 30);

    // Call the second string Orange pulse
    pulse(secondLeds, 150, pulseColorYellow, secondHeadOrange, 0);

    // call second string green pulse
    pulse(secondLeds, 150, pulseColorGreen, secondHeadGreen, 10);

    // Update the changes. Putting this in the Pulse function makes things go much slower
    // Updating the pixels THEN showing the changes is much faster.
    FastLED.show();
    Serial.println(delayDistance);
}

/**
 * Pulse function. intakes Strip Number(the declaration of the LED Strip as an array)
 * NUmber of LEDs in the strip, the color of the pulse, the head variable you want,
 * and the gap between pulses
 */
void pulse(CRGB strip[], const int &ledNumber, int &color, int &head, int gap)
{

    // Get the head skip
    int skip = headSkip(delayDistance);

    // Increment until it hits the end
    if (head <= ledNumber)
    {
        head += skip;
    }

    // reset if too high
    if (head > ledNumber)
    {
        head = 0 - gap;
    }

    // writing color to the head
    if (head >= 0)
    {
        // color the LEDs
        strip[head] = CHSV(colorChange(color), 255, 255);

        // backfill for skipped LEDs
        backFill(strip, skip, head, color);
    }

    // Fade for size
    tailFade(strip, ledNumber, 250);
    delay(1);
}

/**
 * Fade the tail of the LEDs to determine the visual size of the pulse
 * Needs an input between 254 and 200 (200 being the smallest)
 */
// Fade to determine the size of the pulse
void tailFade(CRGB strip[], int ledNumber, int pulseSize)
{
    for (int i = 0; i < ledNumber; i++)
    {
        // 255 is standard, 215 is very small
        strip[i].nscale8(pulseSize);
    }
}

/**
 * Determines the skip distance when interacting with the sensor
 * so that the closer a subject is, the more LEDs the pulse will skip
 *
 */
int headSkip(int &distance)
{
    // translate Sensor reading into headskip scale
    if (40 <= distance)
    {
        return 1;
    }
    else if (20 <= distance < 40)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

/**
 * Fill in behind the Head when it skips (speeds up) an LED
 * Takes in the distance which is updated every loop
 */
void backFill(CRGB strip[], int skipDistance, int head, int color)
{

    for (int i = skipDistance; i > 0; i--)
    {
        int behind = head - i;

        if (behind >= 0)
        {
            strip[behind] = CHSV(colorChange(color), 255, 255);
        }
    }
}

/**
 * Distance measurement. C statement address the pin directly which eliminate the need
 * for digitalWrite();
 */
void measureDist(int &distance)
{
    // C statement to address Trigger Pin directly. Sets to low
    
# 222 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 3
   (*(volatile uint8_t *)((0x0E) + 0x20)) 
# 222 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
         |= 
# 222 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 3
            (1 << (5))
# 222 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
                    ;
    delayMicroseconds(2);
    // C Statement to address Trigger Pin directly. Sets to high
    
# 225 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 3
   (*(volatile uint8_t *)((0x0E) + 0x20)) 
# 225 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
         &= ~
# 225 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 3
             (1 << (5))
# 225 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
                     ;
    delayMicroseconds(10);
    // C Statement to address Trigger Pin directly. Sets to low
    
# 228 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 3
   (*(volatile uint8_t *)((0x0E) + 0x20)) 
# 228 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
         |= 
# 228 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino" 3
            (1 << (5))
# 228 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ManyStrips/ManyStrips.ino"
                    ;

    // Equation for distance calculation condensed into "return"
    // divided by 4 to eliminate "pulseDistance"
    long readerValue = pulseIn(ECHO_PIN, 0x1);
    // Serial.println(readerValue);
    if (readerValue < 9)
    {
        readerValue = 9;
    }

    distance = readerValue * 0.034 / 2;
}

/**
 * Change the color in tandem with the distance measurement. Will only
 * activate within a certain threshold
 */
int colorChange(int &color)
{
    // Check if there's something within the area of the sensor
    if (delayDistance < 50)
    {
        // Resetr the color variable to 0 when it hits 256 (loop)
        if (color > 255)
        {
            color = 0;
        }
        // increment the color if there's something on the sensor.
        color++;
    }
    // return the updated value
    return color;
}
