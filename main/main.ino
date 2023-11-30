#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

// TODO: use onebutton.h
#include "config.h"
#include "EffectsHandler.h"
// #include "ControlHandler.h"
#include "buttons.h"

int mode = EFFECT_MODE;

// OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R0, /* reset=*/21, /* clock=*/18, /* data=*/17);
int g_lineHeight = 0;

CRGB leds[NUM_LEDS] = {0};
int hue = 100;

// Buttons
bool specButtonPressed;
bool auxButtonPressed;
bool secondaryButtonPressed;
bool primaryButtonPressed;
bool encoderButtonPressed;
bool *effectButtons[] = {&primaryButtonPressed, &secondaryButtonPressed, &specButtonPressed, &auxButtonPressed};

unsigned long lastAuxPressedMillis = 0;
unsigned long auxButtonDelay = 500;
// Effects
EffectsHandler effectsHandler;

// Controls
// ControlHandler controlHandler;

// LEDs

void printMsg(const char *msg)
{
    g_OLED.clear();
    g_OLED.clearBuffer();
    g_OLED.home();
    g_OLED.setCursor(0, g_lineHeight);
    g_OLED.printf(msg);
    g_OLED.sendBuffer();
}

void updateDisplay(int data)
{
    char str[32];
    sprintf(str, "Data: %d", data);
    printMsg(str);
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    // LEDs
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
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
    g_OLED.begin();
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent() + 2;
    g_OLED.setCursor(0, g_lineHeight);
    g_OLED.print("Project Cyborg:");
    g_OLED.setCursor(0, 2 * g_lineHeight);
    g_OLED.print("ONLINE");
    g_OLED.sendBuffer();

    // Effects
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
    pollButtons(POLL_RATE);
    if (millis() - lastAuxPressedMillis > auxButtonDelay && auxButtonPressed)
    {
        lastAuxPressedMillis = millis();
        effectsHandler.rotatePreset();
    }
    effectsHandler.handleButtonPress();
    effectsHandler.drawFrame();
}
