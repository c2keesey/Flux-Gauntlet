#ifndef OLEDControl_h
#define OLEDControl_h

#include <Arduino.h>
#include <U8g2lib.h>

class OLEDControl
{
public:
    OLEDControl();
    void init();
    void printMsg(const char *msg);
    void updateDisplay(int data);
    void displayFPSOLED(double fps);
    void printProjectName(char *name);
    void displayEncoder(int encoderPos);
    // Other OLED-related methods can be declared here

private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED;
    int g_lineHeight;
    int maxBrightness;
    int mode;
    // Other private variables and methods can be declared here
};

#endif // OLEDControl_h
