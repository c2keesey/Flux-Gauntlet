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
#define MAX_STRIP_DRAW 500 // TODO: attatch to pin to dynamically adjust
#define LED_BUILTIN 35

// LED Strip
#define NUM_LEDS 300
#define LED_PIN 48
#define BRIGHTNESS 255

// Effects
// #define LIBRARY_SIZE 4
#define NUM_EFFECT_BUTTONS 3

#define NUM_PRESETS 4
#define ACTION_PRESET 0
#define AMBIENT_PRESET 1

#define DEFAULT_PALETTE RainbowColors_p
#define NUM_PALETTES 7

#define PRIMARY_BUTTON 0
#define SECONDARY_BUTTON 1
#define SPEC_BUTTON 2
#define AUX_BUTTON 3

// OLED
#define OLED_FRAME_RATE 30

// Buttons
#define SPEC_BUTTON_PIN 47      // Blue thumb
#define AUX_BUTTON_PIN 46       // White wrist
#define SECONDARY_BUTTON_PIN 45 // Green ring finger
#define PRIMARY_BUTTON_PIN 41   // Red middle finger
#define ENCODER_BUTTON_PIN 40

#define DEBOUNCE_DELAY 50
#define POLL_RATE 5

// Rotary Encoder
#define ENCODER_PIN_A 33
#define ENCODER_PIN_B 34

#endif // G_CONFIG_H
