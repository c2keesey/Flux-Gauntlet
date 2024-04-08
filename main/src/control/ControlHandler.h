#ifndef CONTROLHANDLER_H
#define CONTROLHANDLER_H

#include <Arduino.h>
#include <FastLED.h>

#include "../config/config.h"
#include "../effects/gauntlet/g_EffectsHandler.h"

#define NO_BUTTON 99
#define MODE_CHANGE_DELAY 200
#define ENCODER_POLL_RATE 10

#define HOLD_TIME 500

extern CRGB leds[];

extern bool auxButtonPressed;
extern bool secondaryButtonPressed;
extern bool primaryButtonPressed;
extern bool specButtonPressed;

extern g_EffectsHandler effectsHandler;
// extern EffectLibrary effectLibrary;

class ControlHandler
{
private:
    int mode = EFFECT_MODE;
    enum ControlState : int
    {
        NONE,
        BUTTON_SELECT,
        EFFECT_SELECT,
    };
    ControlState controlState = NONE;
    int preset = -1;
    EffectButton curButton = NONE_BUTTON;
    CRGB effectSettingColor[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
    int encoderPos = 5;
    int lastEncoderPos = 0;
    bool lastAuxButtonState = false;
    unsigned long modeChangeTimer = 0;
    bool modeWasSet = false;
    // Rotary Encoder
    int lastEncoded = 0;
    bool initSet = true;

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
        curButton = NONE_BUTTON;
        initSet = true;
    }

    void handleButtonPress()
    {
        if (controlState == BUTTON_SELECT)
        {
            handleEffectButtonPress();
        }
        else if (controlState == EFFECT_SELECT)
        {
            handleEncoderChange();
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

    void handleEffectButtonPress()
    {
        if (!initSet)
        {
            return;
        }
        if (primaryButtonPressed)
        {
            Serial.println("Primary button pressed");
            handleEffectButtonSelect(PRIMARY_BUTTON);
        }
        else if (secondaryButtonPressed)
        {
            Serial.println("Secondary button pressed");
            handleEffectButtonSelect(SECONDARY_BUTTON);
        }
        else if (specButtonPressed)
        {
            handleEffectButtonSelect(SPEC_BUTTON);
        }
    }

    void handleEffectButtonSelect(EffectButton button)
    {
        initSet = false;
        curButton = button;
        encoderPos = 0;
        effectsHandler.selectButton(button);
        controlState = EFFECT_SELECT;
        // effectsHandler.unsuppressEffects();
    }

    void setMode()
    {
        if (!modeWasSet && lastAuxButtonState && millis() - modeChangeTimer > HOLD_TIME)
        {
            modeWasSet = true;
            if (mode == EFFECT_MODE)
            {
                mode = SET_MODE;
                controlState = BUTTON_SELECT;
            }
            else
            {
                reset();
                mode = EFFECT_MODE;
                controlState = NONE;
            }
            effectsHandler.triggerModeChange(mode);
        }
    }

    void handleAuxButtonPress()
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
        setMode();
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
        if (mode == EFFECT_MODE)
        {
            return;
        }
        if (millis() - lastEncoderPoll > interval)
        {
            updateEncoder();
            lastEncoderPoll = millis();
        }
    }

    void handleEncoderChange()
    {
        if (encoderPos != lastEncoderPos)
        {
            lastEncoderPos = encoderPos;
            effectsHandler.selectEffect(curButton, getPos());
        }
    }
};

#endif // CONTROLHANDLER_H
