#line 1 "/Users/c2k/ArduinoProjects/LEDARMv2/main/config.h"
#ifndef CONFIG_H
#define CONFIG_H

/*
Device config:

Battery voltage 5V
Battery current 3.1A
Device draw 300mA
Per LED draw 60mA
Safety margin ~15%
*/
#define MAX_STRIP_DRAW 2400
#define LED_BUILTIN 35

// LED Strip
#define NUM_LEDS 100
#define LED_PIN 1

// OLED
const long refreshRate = 500;

// Buttons
#define SPEC_BUTTON_PIN 34      // Blue thumb
#define AUX_BUTTON_PIN 47       // White wrist
#define SECONDARY_BUTTON_PIN 48 // Green ring finger
#define PRIMARY_BUTTON_PIN 46   // Red middle finger
#define ENCODER_BUTTON_PIN 45
const long debounceDelay = 50;

// Rotary Encoder
#define ENCODER_PIN_A 33
#define ENCODER_PIN_B 26

#endif // CONFIG_H
