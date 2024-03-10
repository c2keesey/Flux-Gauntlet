#ifndef CONTROLHANDLER_H
#define CONTROLHANDLER_H

#include <Arduino.h>
#include <FastLED.h>

#include "../config/config.h"
#include "../effects/gauntlet/g_EffectsHandler.h"

#define NO_BUTTON 99
#define MODE_CHANGE_DELAY 200
#define ENCODER_POLL_RATE 10

#define EFFECT_MODE 0
#define SET_MODE 1
#define PRESET_MODE 2

#define HOLD_TIME 500

extern CRGB leds[];

extern bool auxButtonPressed;
extern bool secondaryButtonPressed;
extern bool primaryButtonPressed;
extern bool specButtonPressed;

extern g_EffectsHandler effectsHandler;

class ControlHandler
{
private:
    int mode = EFFECT_MODE;
    uint8_t curButton = NO_BUTTON;
    unsigned int curEffect;
    CRGB effectSettingColor[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
    int encoderPos = 5;
    int lastEncoderPos = 0;
    bool lastAuxButtonState = false;
    unsigned long modeChangeTimer = 0;
    bool modeWasSet = false;
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

    void setMode()
    {
        if (!modeWasSet && lastAuxButtonState && millis() - modeChangeTimer > HOLD_TIME)
        {
            modeWasSet = true;
            if (mode == EFFECT_MODE)
            {
                mode = SET_MODE;
            }
            else
            {
                reset();
                mode = EFFECT_MODE;
            }
        }
    }

    int getMode()
    {
        return mode;
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
        if (auxButtonPressed && !lastAuxButtonState)
        {
            modeChangeTimer = millis();
            lastAuxButtonState = true;
            effectsHandler.triggerControl(HOLD_TIME);
        }
        else if (!auxButtonPressed && lastAuxButtonState)
        {
            lastAuxButtonState = false;
            effectsHandler.cancelControl();
            modeWasSet = false;
        }
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
