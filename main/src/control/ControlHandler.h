#ifndef CONTROLHANDLER_H
#define CONTROLHANDLER_H

#include <Arduino.h>
#include <FastLED.h>

#include "../config/config.h"
#include "../effects/gauntlet/g_EffectsHandler.h"
#include "Button.h"

#define NO_BUTTON 99
#define MODE_CHANGE_DELAY 200
#define ENCODER_POLL_RATE 10

#define SET_HOLD_TIME 500
#define PRESET_HOLD_TIME 1000

extern CRGB leds[];

extern Button thumbButton;
extern Button ringfButton;
extern Button middleButton;
extern Button indexButton;
extern Button pinkyButton;
extern Button auxButton;

extern g_EffectsHandler effectsHandler;

class ControlHandler
{

private:
    enum ControlState : int
    {
        EFFECT,
        BUTTON_SELECT,
        EFFECT_SELECT,
        PRESET_SELECT
    };

    ControlState controlState = EFFECT;
    int preset = -1;
    ButtonEnum curButton = NONE_BUTTON;
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
        handleAuxButtonPress();
        if (controlState == BUTTON_SELECT)
        {
            handleEffectButtonPress();
        }
        else if (controlState == EFFECT_SELECT || controlState == PRESET_SELECT)
        {
            pollEncoder(POLL_RATE);
            handleEncoderChange();
        }
    }

    int getControlState()
    {
        return controlState;
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
        if (middleButton.isPressed())
        {
            handleEffectButtonSelect(MIDDLE);
        }
        else if (ringfButton.isPressed())
        {
            handleEffectButtonSelect(RINGF);
        }
        else if (thumbButton.isPressed())
        {
            handleEffectButtonSelect(THUMB);
        }
        else if (indexButton.isPressed())
        {
            handleEffectButtonSelect(INDEX);
        }
        else if (pinkyButton.isPressed())
        {
            handleEffectButtonSelect(PINKY);
        }
    }

    void handleEffectButtonSelect(ButtonEnum button)
    {
        initSet = false;
        curButton = button;
        encoderPos = 0;
        effectsHandler.selectButton(button);
        controlState = EFFECT_SELECT;
        // effectsHandler.unsuppressEffects();
    }

    void setButtonSelect()
    {
        if (controlState == EFFECT)
        {
            controlState = BUTTON_SELECT;
            effectsHandler.triggerButtonSelectMode();
        }
        else
        {
            setEffectMode();
        }
    }

    void setEffectMode()
    {
        reset();
        controlState = EFFECT;
        effectsHandler.triggerEffectMode();
    }

    void setPresetMode()
    {
        if (controlState == EFFECT)
        {
            controlState = PRESET_SELECT;
            effectsHandler.triggerPresetSelectMode();
        }
        else
        {
            setEffectMode();
        }
    }

    void handleAuxButtonPress()
    {
        if (auxButton.isPressed() && !lastAuxButtonState)
        {
            modeChangeTimer = millis();
            lastAuxButtonState = true;
            effectsHandler.triggerControl(SET_HOLD_TIME);
        }
        else if (!auxButton.isPressed() && lastAuxButtonState)
        {
            unsigned long elapsed = millis() - modeChangeTimer;
            if (elapsed > PRESET_HOLD_TIME)
            {
                setPresetMode();
            }
            else if (elapsed > SET_HOLD_TIME)
            {
                setButtonSelect();
            }
            else
            {
                effectsHandler.cancelControl();
            }
            lastAuxButtonState = false;
        }
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
        if (controlState == EFFECT)
        {
            return;
        }
        if (millis() - lastEncoderPoll > interval)
        {
            updateEncoder();
            lastEncoderPoll = millis();
        }
    }

    void pollEncoderTest()
    {
        updateEncoder();
    }

    void handleEncoderChange()
    {
        if (encoderPos >= lastEncoderPos + 2 || encoderPos <= lastEncoderPos - 2)
        {
            lastEncoderPos = encoderPos;
            if (controlState == PRESET_SELECT)
            {
                effectsHandler.selectPreset(getPos());
            }
            else
            {
                effectsHandler.selectEffect(curButton, getPos());
            }
        }
    }
};

#endif // CONTROLHANDLER_H
