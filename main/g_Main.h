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

int mode = EFFECT_MODE;

// OLED
double fps = 0;
int displayRate = 1000;
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

unsigned long lastAuxPressedMillis = 0;
unsigned long auxButtonDelay = 500;
// Effects
g_EffectsHandler effectsHandler;

// Controls
ControlHandler controlHandler;
// int encoderPos = 0;
// int lastEncoderPos = 0;
// int lastEncoded = 0;

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
    oledControl.printProjectName("Flux Gauntlet");
    // Effects

    // Serial
    Serial.begin(9600);
}

void ind()
{
    leds[NUM_LEDS - 14] = CRGB::Red;
    FastLED.show();
}

unsigned long lastMillis = 0;
#define NO_BUTTON 255
int curButton = NO_BUTTON;
CRGB effectSettingColor[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
int curEffects[] = {0, 1, 2};
unsigned long lastColorChangeTime = 0;
unsigned long colorChangeDelay = 300;
void loop()
{
    controlHandler.pollEncoder(POLL_RATE);
    Serial.println(controlHandler.getPos());
    double dStart = millis() / 1000.0;
    if (millis() - lastUpdateDisplay > displayRate)
    {
        lastUpdateDisplay = millis();
        oledControl.displayFPSOLED(fps);
    }
    pollButtons(POLL_RATE);

    if (auxButtonPressed && (millis() - lastAuxPressedMillis > auxButtonDelay))
    {
        lastAuxPressedMillis = millis();
        effectsHandler.rotatePreset();
    }

    effectsHandler.handleButtonPress();
    effectsHandler.drawFrame();
    // if (mode == EFFECT_MODE)
    // {
    //     if (auxButtonPressed && millis() - lastAuxPressedMillis > auxButtonDelay)
    //     {
    //         lastAuxPressedMillis = millis();
    //         mode = SET_MODE;
    //     }
    //     else
    //     {
    //         effectsHandler.handleButtonPress();
    //         effectsHandler.drawFrame();
    //     }
    // }
    // else
    // {
    //     ind();
    //     controlHandler.pollEncoder(POLL_RATE);
    //     if (auxButtonPressed && millis() - lastAuxPressedMillis > auxButtonDelay)
    //     {
    //         lastAuxPressedMillis = millis();
    //         controlHandler.reset();
    //         mode = EFFECT_MODE;
    //     }
    //     else
    //     {
    //         controlHandler.handleButtonPress();
    //         controlHandler.drawFrame();
    //     }
    // }

    fps = FramesPerSecond(millis() / 1000.0 - dStart);
}
