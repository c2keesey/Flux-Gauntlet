#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

#include "src/control/Button.h"
#include "src/config/config.h"
#include "src/effects/gauntlet/g_EffectsHandler.h"
#include "src/control/ControlHandler.h"
#include "src/utils/timing.h"
#include "src/oled/OLEDControl.h"

// OLED
double fps = 0;
int displayRate = 500;
int lastUpdateDisplay = 0;

OLEDControl oledControl;

// LEDs
CRGB leds[NUM_LEDS] = {0};
int hue = 100;

// Buttons
Button thumbButton(THUMBF_BUTTON_PIN, THUMB);
Button indexButton(INDEXF_BUTTON_PIN, INDEX);
Button middleButton(MIDDLEF_BUTTON_PIN, MIDDLE);
Button ringfButton(RINGF_BUTTON_PIN, RINGF);
Button pinkyButton(PINKYF_BUTTON_PIN, PINKY);
Button auxButton(AUX_BUTTON_PIN, AUX);

// Effects
g_EffectsHandler effectsHandler;

// Library
EffectLibrary effectLibrary;

// Controls
ControlHandler controlHandler;

// LEDs

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    // LEDs
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_STRIP_DRAW);

    // Buttons

    pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);

    // Encoder
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);

    // OLED
    oledControl.init();

    // Library
    effectLibrary.init(); // make sure to call this before initializing effects

    // Effects
    effectsHandler.init();

    // Controls
    controlHandler.reset();

    // Serial
    Serial.begin(9600);
}

void loop()
{
    double dStart = millis() / 1000.0;
    if (millis() - lastUpdateDisplay > displayRate)
    {
        lastUpdateDisplay = millis();
        oledControl.clearLines();
        oledControl.addEncoder(controlHandler.getPos());
        oledControl.addFPS(fps);
        oledControl.addBrightness(fps);
        oledControl.addMode(controlHandler.getControlState());
        oledControl.printLines();
    }

    controlHandler.handleButtonPress();

    effectsHandler.handleButtonPress();
    effectsHandler.drawFrame();

    // uint32_t freeHeap = ESP.getFreeHeap();

    // // Print the free heap memory
    // Serial.print("Free Heap: ");
    // Serial.print(freeHeap);
    // Serial.println(" bytes");

    fps = FramesPerSecond(millis() / 1000.0 - dStart);
}
