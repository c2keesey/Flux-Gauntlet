#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

// TODO: use onebutton.h
#include "src/config/config.h"
#include "src/effects/gauntlet/g_EffectsHandler.h"
#include "src/control/ControlHandler.h"
#include "src/control/buttons.h"
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
bool specButtonPressed;
bool auxButtonPressed;
bool secondaryButtonPressed;
bool primaryButtonPressed;
bool encoderButtonPressed;
bool *effectButtons[] = {&primaryButtonPressed, &secondaryButtonPressed, &specButtonPressed};

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
    pinMode(PRIMARY_BUTTON_PIN, INPUT_PULLUP);
    pinMode(SECONDARY_BUTTON_PIN, INPUT_PULLUP);
    pinMode(SPEC_BUTTON_PIN, INPUT_PULLUP);
    pinMode(AUX_BUTTON_PIN, INPUT_PULLUP);
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

void ind()
{
    leds[NUM_LEDS - 14] = CRGB::Red;
    FastLED.show();
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
    pollButtons(POLL_RATE);

    controlHandler.handleButtonPress();

    effectsHandler.handleButtonPress();
    effectsHandler.drawFrame();

    controlHandler.updateEncoder();
    effectsHandler.test(controlHandler.getPos());

    fps = FramesPerSecond(millis() / 1000.0 - dStart);
}
