#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

// TODO: use onebutton.h
#include "config.h"
#include "EffectsHandler.h"
#include "ControlHandler.h"
#include "buttons.h"

int mode = EFFECT_MODE;

// OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R0, /* reset=*/21, /* clock=*/18, /* data=*/17);
int g_lineHeight = 0;
double fps = 0;
int displayRate = 500;
int lastUpdateDisplay = 0;

// LEDs
CRGB leds[NUM_LEDS] = {0};
int hue = 100;
int maxBrightness = 255;

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
ControlHandler controlHandler;
// int encoderPos = 0;
// int lastEncoderPos = 0;
// int lastEncoded = 0;

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

double FramesPerSecond(double seconds)
{
    static double framesPerSecond;
    framesPerSecond = (framesPerSecond * 0.9) + (1.0 / seconds * 0.1);
    return framesPerSecond;
}

// void updateEncoder()
// {
//     int MSB = digitalRead(ENCODER_PIN_A); // MSB = most significant bit
//     int LSB = digitalRead(ENCODER_PIN_B); // LSB = least significant bit

//     int encoded = (MSB << 1) | LSB;         // converting the 2 pin value to single number
//     int sum = (lastEncoded << 2) | encoded; // adding it to the previous encoded value

//     if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
//         encoderPos++;
//     if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
//         encoderPos--;

//     lastEncoded = encoded; // store this value for next time
// }

void displayFPS()
{
    g_OLED.clearBuffer();
    g_OLED.setCursor(0, g_lineHeight);
    g_OLED.printf("FPS: %u", FastLED.getFPS());
    g_OLED.setCursor(0, g_lineHeight * 2 + 2);
    g_OLED.printf("Brite: %u mW", calculate_max_brightness_for_power_mW(maxBrightness, MAX_STRIP_DRAW));
    g_OLED.setCursor(0, g_lineHeight * 3 + 2);
    g_OLED.printf("Mode: %s", mode == EFFECT_MODE ? "Effect" : "Control");
    g_OLED.sendBuffer();
}

// void displayEncoder()
// {
//     g_OLED.clearBuffer();
//     g_OLED.setCursor(0, g_lineHeight * 2 + 2);
//     g_OLED.printf("Encoder: %d", encoderPos);
//     g_OLED.sendBuffer();
// }

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
    g_OLED.begin();
    g_OLED.setFlipMode(1);
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
    double dStart = millis() / 1000.0;
    if (millis() - lastUpdateDisplay > displayRate)
    {
        lastUpdateDisplay = millis();
        displayFPS();
    }
    pollButtons(POLL_RATE);
    if (mode == EFFECT_MODE)
    {
        if (auxButtonPressed && millis() - lastAuxPressedMillis > auxButtonDelay)
        {
            lastAuxPressedMillis = millis();
            mode = SET_MODE;
        }
        else
        {
            effectsHandler.handleButtonPress();
            effectsHandler.drawFrame();
        }
    }
    else
    {
        ind();
        controlHandler.pollEncoder(POLL_RATE);
        if (auxButtonPressed && millis() - lastAuxPressedMillis > auxButtonDelay)
        {
            lastAuxPressedMillis = millis();
            controlHandler.reset();
            mode = EFFECT_MODE;
        }
        else
        {
            controlHandler.handleButtonPress();
            controlHandler.drawFrame();
        }
    }

    fps = FramesPerSecond(millis() / 1000.0 - dStart);
}
