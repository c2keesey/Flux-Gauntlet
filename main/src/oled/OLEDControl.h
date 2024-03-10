#ifndef OLEDControl_h
#define OLEDControl_h

#include <Arduino.h>
#include <U8g2lib.h>
#include <vector>
#include <string>

#define MAX_LINES 4
class OLEDControl
{
public:
    OLEDControl();
    void init();
    void addMsg(const char *msg);
    void addUpdateDisplay(int data);
    void addFPS(double fps);
    void addBrightness(double fps);
    void addProjectName(char *name);
    void addEncoder(int encoderPos);
    void addMode(int mode);
    void clearLines();
    void printLines();

private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED;
    int g_lineHeight;
    int maxBrightness;
    std::vector<std::string> lines;
    // Other private variables and methods can be declared here
};

#endif // OLEDControl_h
