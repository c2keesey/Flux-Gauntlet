#include "OLEDControl.h"
#include <FastLED.h>
#include "../config/config.h"

OLEDControl::OLEDControl()
    : g_OLED(U8G2_R0, /* reset=*/21, /* clock=*/18, /* data=*/17), g_lineHeight(0), maxBrightness(255), mode(EFFECT_MODE)
{
}

void OLEDControl::init()
{
    g_OLED.begin();
    g_OLED.setFlipMode(1);
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent() + 2;
}

void OLEDControl::printMsg(const char *msg)
{
    g_OLED.clearBuffer();
    g_OLED.setCursor(0, g_lineHeight);
    g_OLED.printf(msg);
    g_OLED.sendBuffer();
}

void OLEDControl::updateDisplay(int data)
{
    char str[32];
    sprintf(str, "Data: %d", data);
    printMsg(str);
}

void OLEDControl::displayFPSOLED(double fps)
{
    g_OLED.clearBuffer();
    g_OLED.setCursor(0, g_lineHeight * 4);
    g_OLED.printf("FPS: %u", fps);
    g_OLED.setCursor(0, g_lineHeight * 2 + 2);
    g_OLED.printf("Brite: %u mW", calculate_max_brightness_for_power_mW(maxBrightness, MAX_STRIP_DRAW));
    g_OLED.sendBuffer();
}

void OLEDControl::printProjectName(char *name)
{

    g_OLED.setCursor(0, g_lineHeight);
    g_OLED.print("Project:");
    g_OLED.setCursor(0, g_lineHeight * 2 + 2);
    g_OLED.print(name);
    g_OLED.setCursor(0, 3 * g_lineHeight + 4);
    g_OLED.print("ONLINE");
    g_OLED.sendBuffer();
}

void OLEDControl::displayEncoder(int encoderPos)
{
    g_OLED.clearBuffer();
    g_OLED.setCursor(0, g_lineHeight * 2 + 2);
    g_OLED.printf("Encoder: %d", encoderPos);
    g_OLED.sendBuffer();
}
