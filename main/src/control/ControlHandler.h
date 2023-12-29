#ifndef CONTROLHANDLER_H
#define CONTROLHANDLER_H

#include <Arduino.h>
#include <FastLED.h>

#include "../config/config.h"

#define NO_BUTTON 99
#define MODE_CHANGE_DELAY 200
#define ENCODER_POLL_RATE 10

extern int mode;

extern CRGB leds[];

extern bool auxButtonPressed;
extern bool secondaryButtonPressed;
extern bool primaryButtonPressed;
extern bool specButtonPressed;

class ControlHandler
{
private:
    uint8_t curButton = NO_BUTTON;
    unsigned int curEffect;
    CRGB effectSettingColor[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
    unsigned long modeChangeTime = 0;
    int encoderPos = 5;
    int lastEncoderPos = 0;

    // Rotary Encoder
    int lastEncoded = 0;

    unsigned long lastEncoderPoll = 0;

public:
    ControlHandler()
    {
    }

    ~ControlHandler()
    {
    }

    void reset()
    {
        encoderPos = 0;
        lastEncoderPos = 0;
        curButton = NO_BUTTON;
    }

    int getPos()
    {
        return encoderPos;
    }

    void setCurButton(uint8_t button)
    {
        curButton = button;
    }

    void handleButtonPress()
    {
    }

    // void handleEncoderChange()
    // {
    //     if (encoderPos == lastEncoderPos)
    //     {
    //         return;
    //     }
    //     if (curButton == NO_BUTTON)
    //     {
    //         return;
    //     }
    //     if (encoderPos < 0)
    //     {
    //         curEffect = (LIBRARY_SIZE - (-encoderPos % LIBRARY_SIZE)) % LIBRARY_SIZE;
    //     }
    //     else
    //     {
    //         curEffect = encoderPos % LIBRARY_SIZE;
    //     }
    //     lastEncoderPos = encoderPos;
    //     effectsHandler.updateEffect(curButton, curEffect);
    // }

    void drawFrame()
    {
        if (curButton == NO_BUTTON)
        {
            return;
        }
        for (int i = NUM_LEDS - 1; i > NUM_LEDS - curEffect - 2; i--)
        {
            leds[i] = effectSettingColor[curButton];
        }
        FastLED.show();
    }

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

    void pollEncoder(unsigned long interval)
    {
        if (millis() - lastEncoderPoll > interval)
        {
            updateEncoder();
            lastEncoderPoll = millis();
        }
    }
};

#endif // CONTROLHANDLER_H
