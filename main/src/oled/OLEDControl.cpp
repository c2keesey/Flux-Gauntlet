#include "OLEDControl.h"
#include <FastLED.h>
#include "../config/config.h"

OLEDControl::OLEDControl()
    : g_OLED(U8G2_R0, /* reset=*/21, /* clock=*/18, /* data=*/17), g_lineHeight(0), maxBrightness(255)
{
}

void OLEDControl::init()
{
    g_OLED.begin();
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent() + 2;
}

void OLEDControl::clearLines()
{
    lines.clear();
}

void OLEDControl::addMsg(const char *msg)
{
    if (lines.size() < MAX_LINES)
    {
        lines.push_back(msg);
    }
}

void OLEDControl::addUpdateDisplay(int data)
{
    if (lines.size() < MAX_LINES)
    {
        char str[32];
        sprintf(str, "Data: %d", data);
        lines.push_back(str);
    }
}

void OLEDControl::addFPS(double fps)
{
    if (lines.size() < MAX_LINES)
    {
        char fpsStr[32];
        sprintf(fpsStr, "FPS: %.2f", fps);
        lines.push_back(fpsStr);
    }
}

void OLEDControl::addBrightness(double fps)
{
    if (lines.size() < MAX_LINES)
    {
        char briteStr[32];
        sprintf(briteStr, "Brite: %u mW", calculate_max_brightness_for_power_mW(maxBrightness, MAX_STRIP_DRAW));
        lines.push_back(briteStr);
    }
}

void OLEDControl::addProjectName(char *name)
{
    if (lines.size() + 2 < MAX_LINES)
    { // Checking space for three lines
        lines.push_back("Project:");
        lines.push_back(name);
        lines.push_back("ONLINE");
    }
}

void OLEDControl::addEncoder(int encoderPos)
{
    if (lines.size() < MAX_LINES)
    {
        char encoderStr[32];
        sprintf(encoderStr, "Encoder: %d", encoderPos);
        lines.push_back(encoderStr);
    }
}

void OLEDControl::addMode(int mode)
{
    if (lines.size() < MAX_LINES)
    {
        char modeStr[32];
        sprintf(modeStr, "Mode: %d", mode);
        lines.push_back(modeStr);
    }
}

void OLEDControl::printLines()
{
    g_OLED.clearBuffer();
    int lineCount = 0;
    for (const auto &line : lines)
    {
        g_OLED.setCursor(0, (++lineCount) * g_lineHeight);
        g_OLED.print(line.c_str());
    }
    g_OLED.sendBuffer();
    lines.clear();
}
