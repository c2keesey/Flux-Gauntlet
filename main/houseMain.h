#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

// TODO: use onebutton.h
#include "src/config/config.h"
#include "src/effects/EffectsHandler.h"
#include "src/utils/timing.h"
#include "src/oled/OLEDControl.h"

// OLED
OLEDControl oledControl;

double fps = 0;
int displayRate = 1000;
int lastUpdateDisplay = 0;

// LEDs
CRGB leds[NUM_LEDS] = {0};
int hue = 100;
int maxBrightness = 255;

// Effects
EffectsHandler effectsHandler;

// LEDs

void sendStats()
{
    Serial.print("FPS: ");
    Serial.print(fps);
    Serial.print(" Brite: ");
    Serial.print(calculate_max_brightness_for_power_mW(maxBrightness, MAX_STRIP_DRAW));
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    // LEDs
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_STRIP_DRAW);

    // OLED
    oledControl.init();
    oledControl.printProjectName("Flux Arch");

    // Effects

    // Serial
    Serial.begin(9600);
}

void loop()
{
    double dStart = millis() / 1000.0;

    if (millis() - lastUpdateDisplay > displayRate)
    {
        lastUpdateDisplay = millis();
        oledControl.displayFPSOLED(fps);
    }

    effectsHandler.drawFrame();

    fps = FramesPerSecond(millis() / 1000.0 - dStart);
}
