#line 1 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

#include "config.h"
#include "EffectsHandler.h"
#include "buttons.h"

// OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R0, /* reset=*/21, /* clock=*/18, /* data=*/17);
int g_lineHeight = 0;
unsigned long lastRefresh = 0;

CRGB leds[NUM_LEDS] = {0};
int hue = 100;

// Buttons
volatile bool buttonPressed = false;
volatile int presses = 0;
volatile int lastPresses = 0;

unsigned long lastDebounceTime = 0;

// Effects
EffectsHandler effectsHandler;

// Rotary Encoder
volatile int encoderPos = 0;
volatile int lastEncoded = 0;
int lastPos = 0;

#line 33 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
void updateEncoder();
#line 49 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
void updateDisplay(int data);
#line 56 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
void printMsg(const char *msg);
#line 66 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
void setup();
#line 113 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
void loop();
#line 33 "/Users/c2k/ArduinoProjects/LEDARMv2/main/main.ino"
void updateEncoder()
{
    int MSB = digitalRead(ENCODER_PIN_A); // MSB = most significant bit
    int LSB = digitalRead(ENCODER_PIN_B); // LSB = least significant bit

    int encoded = (MSB << 1) | LSB;         // converting the 2 pin value to single number
    int sum = (lastEncoded << 2) | encoded; // adding it to the previous encoded value

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
        encoderPos++;
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
        encoderPos--;

    lastEncoded = encoded; // store this value for next time
}

void updateDisplay(int data)
{
    char str[32];
    sprintf(str, "Data: %d", data);
    printMsg(str);
}

void printMsg(const char *msg)
{
    g_OLED.clear();
    g_OLED.clearBuffer();
    g_OLED.home();
    g_OLED.setCursor(0, g_lineHeight);
    g_OLED.printf(msg);
    g_OLED.sendBuffer();
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
    attachInterrupt(digitalPinToInterrupt(PRIMARY_BUTTON_PIN), handlePrimaryButtonPress, RISING);

    pinMode(SECONDARY_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SECONDARY_BUTTON_PIN), handleSecondaryButtonPress, RISING);

    pinMode(SPEC_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SPEC_BUTTON_PIN), handleSpecButtonPress, RISING);

    pinMode(AUX_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(AUX_BUTTON_PIN), handleAuxButtonPress, RISING);

    pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_BUTTON_PIN), handleEncoderButtonPress, RISING);

    // Encoder
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), updateEncoder, CHANGE);

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

void loop()
{
    effectsHandler.drawFrame();

    if (buttonPressed && (millis() - lastDebounceTime) > debounceDelay)
    {
        presses++;
        buttonPressed = false;
        lastDebounceTime = millis();
    }
    if (lastPos != encoderPos / 2)
    {
        lastPos = encoderPos / 2;
        updateDisplay(encoderPos / 2);
    }
}
