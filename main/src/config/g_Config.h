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

// Set to 2400 for battery use
#define MAX_STRIP_DRAW 2400 // TODO: attatch to voltage pin to dynamically adjust?

#define LED_BUILTIN 35

// LED Strip
#define NUM_LEDS 300
#define LED_PIN 48
#define BRIGHTNESS 255

// Effects
// #define LIBRARY_SIZE 4

#define NUM_PRESETS 2

#define NUM_PALETTES 7

#define AUX_BUTTON 3

#define NUM_EFFECT_BUTTONS 5
enum ButtonEnum
{

    NONE_BUTTON = -1,
    MIDDLE = 0,
    RINGF = 1,
    THUMB = 2,
    INDEX = 3,
    PINKY = 4,
    AUX = 5,
};

// OLED
#define OLED_FRAME_RATE 30

// Buttons
#define THUMBF_BUTTON_PIN 38
#define INDEXF_BUTTON_PIN 39
#define MIDDLEF_BUTTON_PIN 47
#define RINGF_BUTTON_PIN 45
#define PINKYF_BUTTON_PIN 41

#define AUX_BUTTON_PIN 46
#define ENCODER_BUTTON_PIN 40

#define DEBOUNCE_DELAY 50
#define POLL_RATE 1

// Rotary Encoder
#define ENCODER_PIN_A 33
#define ENCODER_PIN_B 34

#endif // G_CONFIG_H
