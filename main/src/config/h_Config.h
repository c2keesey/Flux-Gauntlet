#ifndef H_CONFIG_H
#define H_CONFIG_H

/*
Device config:

Power supply voltage 5V
Power supply power 60W
Device draw 300mA
Per LED draw 60mA
Safety margin ~15%
*/
#define MAX_STRIP_DRAW 2200 // mA
#define LED_BUILTIN 35

#define EFFECT_MODE 0

// LED Strip
// Balcony Front Left and Right strips
#define NUM_BFR 263
#define NUM_BFL 298
#define BFL_CORNER 123
#define BFR_CORNER 439
#define BF_CENTER 281
const int NUM_LEDS = NUM_BFR + NUM_BFL;

#define PIN_BFL 1
#define PIN_BFR 48
#define BRIGHTNESS 255

// Effects
#define LIBRARY_SIZE 4
#define NUM_EFFECT_BUTTONS 3

#define NUM_PRESETS 3
#define ACTION_PRESET 0
#define AMBIENT_PRESET 1

#define NUM_PALETTES 6

// OLED
#define OLED_FRAME_RATE 30

// Buttons
#define THUMB_PIN 34      // Blue thumb
#define AUX_BUTTON_PIN 47 // White wrist
#define RINGF_PIN 48      // Green ring finger
#define MIDDLE_PIN 46     // Red middle finger
#define ENCODER_BUTTON_PIN 45
#define DEBOUNCE_DELAY 50
#define POLL_RATE 5

// Rotary Encoder
#define ENCODER_PIN_A 33
#define ENCODER_PIN_B 26

// From g_Config.h for compilation

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

#endif // H_CONFIG_H
