// buttons.h

#ifndef BUTTONS_H
#define BUTTONS_H

#include "config.h"

extern bool specButtonPressed;
extern bool auxButtonPressed;
extern bool secondaryButtonPressed;
extern bool primaryButtonPressed;
extern bool encoderButtonPressed;

unsigned long lastPoll = 0;

unsigned long lastSpecButtonToggle = 0;
unsigned long lastAuxButtonToggle = 0;
unsigned long lastSecondaryButtonToggle = 0;
unsigned long lastPrimaryButtonToggle = 0;
unsigned long lastEncoderButtonToggle = 0;

void handleButtonPress(int pinNumber)
{
    unsigned long currentMillis = millis();

    switch (pinNumber)
    {
    case SPEC_BUTTON_PIN:
        if (currentMillis - lastSpecButtonToggle >= DEBOUNCE_DELAY)
        {
            specButtonPressed = true;
            lastSpecButtonToggle = currentMillis;
        }
        break;
    case AUX_BUTTON_PIN:
        if (currentMillis - lastAuxButtonToggle >= DEBOUNCE_DELAY)
        {
            auxButtonPressed = true;
            lastAuxButtonToggle = currentMillis;
        }
        break;
    case SECONDARY_BUTTON_PIN:
        if (currentMillis - lastSecondaryButtonToggle >= DEBOUNCE_DELAY)
        {
            secondaryButtonPressed = true;
            lastSecondaryButtonToggle = currentMillis;
        }
        break;
    case PRIMARY_BUTTON_PIN:
        if (currentMillis - lastPrimaryButtonToggle >= DEBOUNCE_DELAY)
        {
            primaryButtonPressed = true;
            lastPrimaryButtonToggle = currentMillis;
        }
        break;
    case ENCODER_BUTTON_PIN:
        if (currentMillis - lastEncoderButtonToggle >= DEBOUNCE_DELAY)
        {
            encoderButtonPressed = true;
            lastEncoderButtonToggle = currentMillis;
        }
        break;
    }
}

void handleButtonRelease(int pinNumber)
{
    unsigned long currentMillis = millis();

    switch (pinNumber)
    {
    case SPEC_BUTTON_PIN:
        if (currentMillis - lastSpecButtonToggle >= DEBOUNCE_DELAY)
        {
            specButtonPressed = false;
            lastSpecButtonToggle = currentMillis;
        }
        break;
    case AUX_BUTTON_PIN:
        if (currentMillis - lastAuxButtonToggle >= DEBOUNCE_DELAY)
        {
            auxButtonPressed = false;
            lastAuxButtonToggle = currentMillis;
        }
        break;
    case SECONDARY_BUTTON_PIN:
        if (currentMillis - lastSecondaryButtonToggle >= DEBOUNCE_DELAY)
        {
            secondaryButtonPressed = false;
            lastSecondaryButtonToggle = currentMillis;
        }
        break;
    case PRIMARY_BUTTON_PIN:
        if (currentMillis - lastPrimaryButtonToggle >= DEBOUNCE_DELAY)
        {
            primaryButtonPressed = false;
            lastPrimaryButtonToggle = currentMillis;
        }
        break;
    case ENCODER_BUTTON_PIN:
        if (currentMillis - lastEncoderButtonToggle >= DEBOUNCE_DELAY)
        {
            encoderButtonPressed = false;
            lastEncoderButtonToggle = currentMillis;
        }
        break;
    }
}

void pollButtons(unsigned long interval)
{
    if (millis() - lastPoll > interval)
    {
        lastPoll = millis();
        if (digitalRead(SPEC_BUTTON_PIN) == LOW)
        {
            handleButtonPress(SPEC_BUTTON_PIN);
        }
        else
        {
            handleButtonRelease(SPEC_BUTTON_PIN);
        }
        if (digitalRead(AUX_BUTTON_PIN) == LOW)
        {
            handleButtonPress(AUX_BUTTON_PIN);
        }
        else
        {
            handleButtonRelease(AUX_BUTTON_PIN);
        }
        if (digitalRead(SECONDARY_BUTTON_PIN) == LOW)
        {
            handleButtonPress(SECONDARY_BUTTON_PIN);
        }
        else
        {
            handleButtonRelease(SECONDARY_BUTTON_PIN);
        }
        if (digitalRead(PRIMARY_BUTTON_PIN) == LOW)
        {
            handleButtonPress(PRIMARY_BUTTON_PIN);
        }
        else
        {
            handleButtonRelease(PRIMARY_BUTTON_PIN);
        }
        if (digitalRead(ENCODER_BUTTON_PIN) == LOW)
        {
            handleButtonPress(ENCODER_BUTTON_PIN);
        }
        else
        {
            handleButtonRelease(ENCODER_BUTTON_PIN);
        }
    }
}

#endif // BUTTONS_H
