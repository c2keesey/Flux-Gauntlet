#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

// TODO: use onebutton.h
#include "src/config/config.h"
#include "src/effects/house/h_EffectsHandler.h"
#include "src/utils/timing.h"
#include "src/oled/OLEDControl.h"

// OLED
OLEDControl oledControl;

double fps = 0;
int displayRate = 1000;
int lastUpdateDisplay = 0;

// LEDs
CRGB bfr_leds[NUM_BFR] = {0};
CRGB bfl_leds[NUM_BFL] = {0};
CRGB *leds[NUM_BFL + NUM_BFR] = {0};
int hue = 100;
int maxBrightness = 255;

// Effects
h_EffectsHandler effectsHandler;

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
    pinMode(PIN_BFL, OUTPUT);
    pinMode(PIN_BFR, OUTPUT);

    FastLED.addLeds<WS2812, PIN_BFL, GRB>(bfl_leds, NUM_BFL);
    FastLED.addLeds<WS2812, PIN_BFR, GRB>(bfr_leds, NUM_BFR);

    for (int i = 0; i < NUM_BFL; i++)
    {
        leds[i] = &bfl_leds[i];
    }
    for (int i = 0; i < NUM_BFR; i++)
    {
        leds[NUM_BFL + i] = &bfr_leds[NUM_BFR - i - 1];
    }
    FastLED.clear();
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_STRIP_DRAW);

    // OLED
    oledControl.init();
    oledControl.printProjectName("Flux Arch");

    // Effects

    // Serial
    Serial.begin(9600);
    randomSeed(analogRead(0));
}

void loop()
{
    static unsigned long lastLoopStart = 0;
    unsigned long loopStart = millis();
    double loopTime = 0;

    if (lastLoopStart != 0)
    {
        loopTime = (loopStart - lastLoopStart) / 1000.0;
        if (loopTime > 0)
        {
            fps = FramesPerSecond(loopTime);
        }
    }

    lastLoopStart = loopStart;
    EVERY_N_SECONDS(random(2, 5))
    {
        effectsHandler.triggerEffect(0);
    }

    EVERY_N_MINUTES(random(5, 10))
    {
        for (int i = 0; i < 10; i++)
        {
            effectsHandler.triggerEffect(0);
        }
    }
    effectsHandler.drawFrame();

    // if (millis() - lastUpdateDisplay > displayRate)
    // {
    //     lastUpdateDisplay = millis();
    //     oledControl.displayFPSOLED(fps);
    //     sendStats();
    // }
}
