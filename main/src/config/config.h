#ifndef G_CONFIG_H
#define G_CONFIG_H

/*
Device config:

Battery voltage 5V
Battery current 3.1A
Device draw 300mA
Per LED draw 60mA
Safety margin ~15%

Pinout: https://resource.heltec.cn/download/WiFi_Kit_32_V3/HTIT-WB32_V3.png

*/
#define MAX_STRIP_DRAW 500 // TODO: attatch to voltage pin to dynamically adjust
#define LED_BUILTIN 35

// LED Strip
#define NUM_LEDS 300
#define LED_PIN 48
#define BRIGHTNESS 255

// Effects
// #define LIBRARY_SIZE 4
#define NUM_EFFECT_BUTTONS 3

#define NUM_PRESETS 2
enum class Preset : int
{
    ACTION,
    TEST,
};

#define DEFAULT_PALETTE RainbowColors_p
#define NUM_PALETTES 7

#define AUX_BUTTON 3

enum EffectButton
{
    NONE_BUTTON = -1,
    PRIMARY_BUTTON = 0,
    SECONDARY_BUTTON = 1,
    SPEC_BUTTON = 2,
};

#define EFFECT_MODE 0
#define SET_MODE 1
#define PRESET_MODE 2

// OLED
#define OLED_FRAME_RATE 30

// Buttons
#define SPEC_BUTTON_PIN 47      // Blue thumb
#define AUX_BUTTON_PIN 46       // White wrist
#define SECONDARY_BUTTON_PIN 45 // Green ring finger
#define PRIMARY_BUTTON_PIN 41   // Red middle finger
#define ENCODER_BUTTON_PIN 40

#define DEBOUNCE_DELAY 50
#define POLL_RATE 1

// Rotary Encoder
#define ENCODER_PIN_A 33
#define ENCODER_PIN_B 34

#endif // G_CONFIG_H
