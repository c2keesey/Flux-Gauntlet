// BUTTONSELECT_H
#ifndef BUTTONSELECT_H
#define BUTTONSELECT_H

#include "../../../shared/effects/BaseEffect.h"
#include "../../../shared/EffectHelpers.h"
#include "../../../../config/config.h"

class ButtonSelect : public BaseEffect
{
private:
    ButtonEnum button = NONE_BUTTON;
    uint8_t hue = 0;
    bool fadeIn = true;
    uint16_t flashVal = 1; // 16-bit to prevent overflow
    uint8_t numFlashes = 0;
    uint8_t flashInc = 20;

public:
    ButtonSelect(ColorPalette pal = rainbow_cp) : BaseEffect(pal) {}

    void trigger() override
    {
        return;
    }

    void setButton(ButtonEnum button)
    {
        this->button = button;
        numFlashes = 0;
    }

    void displayNone()
    {
        vleds[NUM_LEDS - 1] = CHSV(hue, 255, 150);
        vleds[NUM_LEDS - 2] = CHSV(hue + 10, 255, 150);
        vleds[NUM_LEDS - 3] = CHSV(hue + 20, 255, 150);
        vleds[NUM_LEDS - 4] = CHSV(hue + 30, 255, 150);
        vleds[NUM_LEDS - 5] = CHSV(hue + 40, 255, 150);
        hue += 2;
    }

    void signalSelectFlash(int i)
    {
        for (int j = 0; j < i; j++)
        {
            vleds[NUM_LEDS - j - 1] = CHSV(hue, 255, flashVal);
        }
        hue += 3;
        if (fadeIn)
        {
            flashVal += flashInc;
            if (flashVal >= 255)
            {
                fadeIn = false;
            }
        }
        else
        {
            if (flashVal < flashInc)
            {
                flashVal = 0;
            }
            else
            {
                flashVal -= flashInc;
            }
            if (flashVal == 0)
            {
                fadeIn = true;
                numFlashes++;
            }
        }
    }

    void update() override
    {
        clearVleds(vleds);
        if (numFlashes >= 2)
        {
            return;
        }
        if (button == NONE_BUTTON)
        {
            displayNone();
        }
        else
        {
            signalSelectFlash(button + 1);
        }
    }

    void reset()
    {
        hue = 0;
        flashVal = 1;
        fadeIn = true;
        button = NONE_BUTTON;
        numFlashes = 0;
    }
};

#endif // BUTTONSELECT_H