// // buttons.h

// #ifndef BUTTONS_H
// #define BUTTONS_H

// #include "../config/config.h"
// #include <Arduino.h>

// extern bool thumbButton.isPressed();
// extern bool auxButton.isPressed();
// extern bool ringfButton.isPressed();
// extern bool middleButton.isPressed();
// extern bool encoderButtonPressed;

// unsigned long lastPoll = 0;

// unsigned long lastSpecButtonToggle = 0;
// unsigned long lastAuxButtonToggle = 0;
// unsigned long lastSecondaryButtonToggle = 0;
// unsigned long lastPrimaryButtonToggle = 0;
// unsigned long lastEncoderButtonToggle = 0;

// void handleButtonPress(int pinNumber)
// {
//     unsigned long currentMillis = millis();

//     switch (pinNumber)
//     {
//     case THUMB_PIN:
//         if (currentMillis - lastSpecButtonToggle >= DEBOUNCE_DELAY)
//         {
//             thumbButton.isPressed() = true;
//             lastSpecButtonToggle = currentMillis;
//         }
//         break;
//     case AUX_BUTTON_PIN:
//         if (currentMillis - lastAuxButtonToggle >= DEBOUNCE_DELAY)
//         {
//             auxButton.isPressed() = true;
//             lastAuxButtonToggle = currentMillis;
//         }
//         break;
//     case RINGF_PIN:
//         if (currentMillis - lastSecondaryButtonToggle >= DEBOUNCE_DELAY)
//         {
//             ringfButton.isPressed() = true;
//             lastSecondaryButtonToggle = currentMillis;
//         }
//         break;
//     case MIDDLE_PIN:
//         if (currentMillis - lastPrimaryButtonToggle >= DEBOUNCE_DELAY)
//         {
//             middleButton.isPressed() = true;
//             lastPrimaryButtonToggle = currentMillis;
//         }
//         break;
//     case ENCODER_BUTTON_PIN:
//         if (currentMillis - lastEncoderButtonToggle >= DEBOUNCE_DELAY)
//         {
//             encoderButtonPressed = true;
//             lastEncoderButtonToggle = currentMillis;
//         }
//         break;
//     }
// }

// void handleButtonRelease(int pinNumber)
// {
//     unsigned long currentMillis = millis();

//     switch (pinNumber)
//     {
//     case THUMB_PIN:
//         if (currentMillis - lastSpecButtonToggle >= DEBOUNCE_DELAY)
//         {
//             thumbButton.isPressed() = false;
//             lastSpecButtonToggle = currentMillis;
//         }
//         break;
//     case AUX_BUTTON_PIN:
//         if (currentMillis - lastAuxButtonToggle >= DEBOUNCE_DELAY)
//         {
//             auxButton.isPressed() = false;
//             lastAuxButtonToggle = currentMillis;
//         }
//         break;
//     case RINGF_PIN:
//         if (currentMillis - lastSecondaryButtonToggle >= DEBOUNCE_DELAY)
//         {
//             ringfButton.isPressed() = false;
//             lastSecondaryButtonToggle = currentMillis;
//         }
//         break;
//     case MIDDLE_PIN:
//         if (currentMillis - lastPrimaryButtonToggle >= DEBOUNCE_DELAY)
//         {
//             middleButton.isPressed() = false;
//             lastPrimaryButtonToggle = currentMillis;
//         }
//         break;
//     case ENCODER_BUTTON_PIN:
//         if (currentMillis - lastEncoderButtonToggle >= DEBOUNCE_DELAY)
//         {
//             encoderButtonPressed = false;
//             lastEncoderButtonToggle = currentMillis;
//         }
//         break;
//     }
// }

// void pollButtons(unsigned long interval)
// {
//     if (millis() - lastPoll > interval)
//     {
//         lastPoll = millis();
//         if (digitalRead(THUMB_PIN) == LOW)
//         {
//             handleButtonPress(THUMB_PIN);
//         }
//         else
//         {
//             handleButtonRelease(THUMB_PIN);
//         }
//         if (digitalRead(AUX_BUTTON_PIN) == LOW)
//         {
//             handleButtonPress(AUX_BUTTON_PIN);
//         }
//         else
//         {
//             handleButtonRelease(AUX_BUTTON_PIN);
//         }
//         if (digitalRead(RINGF_PIN) == LOW)
//         {
//             handleButtonPress(RINGF_PIN);
//         }
//         else
//         {
//             handleButtonRelease(RINGF_PIN);
//         }
//         if (digitalRead(MIDDLE_PIN) == LOW)
//         {
//             handleButtonPress(MIDDLE_PIN);
//         }
//         else
//         {
//             handleButtonRelease(MIDDLE_PIN);
//         }
//         if (digitalRead(ENCODER_BUTTON_PIN) == LOW)
//         {
//             handleButtonPress(ENCODER_BUTTON_PIN);
//         }
//         else
//         {
//             handleButtonRelease(ENCODER_BUTTON_PIN);
//         }
//     }
// }

// #endif // BUTTONS_H
