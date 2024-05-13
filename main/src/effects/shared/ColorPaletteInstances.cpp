#include "ColorPaletteInstances.h"
#include <vector>

// Define color palettes here.
// Style guide: Use the name of the palette followed by "_cp" as the variable name.
// Should have at least 5 colors to be used as full palette.
// 2 color palettes will have a spread between the two colors.
// Add CHSV(0,0,0) to indicate no spread.

std::vector<CHSV> rainbowColors = {
    CHSV(0, 255, 255),   // Red
    CHSV(32, 255, 255),  // Orange
    CHSV(64, 255, 255),  // Yellow
    CHSV(96, 255, 255),  // Green
    CHSV(128, 255, 255), // Cyan
    CHSV(160, 255, 255), // Blue
    CHSV(192, 255, 255), // Purple
    CHSV(224, 255, 255)  // Pink
};

ColorPalette rainbow_cp(rainbowColors);

std::vector<CHSV> greenDragon = {
    CHSV(74, 255, 255),  // Green-yellow
    CHSV(132, 255, 255), // Green-blue
};

ColorPalette greenDragon_cp(greenDragon);

std::vector<CHSV> purple = {
    CHSV(176, 255, 255), // Blue-purple
    CHSV(200, 255, 255), // Pink-purple
};

ColorPalette purple_cp(purple);

std::vector<CHSV> fire = {
    CHSV(0, 255, 255),  // Red
    CHSV(28, 255, 255), // Light Orange
};

ColorPalette fire_cp(fire);

std::vector<CHSV> america = {
    CHSV(0, 255, 255),   // Red
    CHSV(160, 255, 255), // Blue
    CHSV(0, 0, 255),     // White
};

ColorPalette america_cp(america);

std::vector<CHSV> christmas = {
    CHSV(0, 255, 255),  // Red
    CHSV(96, 255, 255), // Green
    CHSV(0, 0, 0),      // Not spread
};

ColorPalette christmas_cp(christmas);

std::vector<CHSV> mecha = {
    CHSV(12, 255, 255),  // Orange
    CHSV(132, 255, 255), // Cyan
    CHSV(0, 0, 0),       // Not spread
};

ColorPalette mecha_cp(mecha);

std::vector<CHSV> ice = {
    CHSV(134, 255, 255), // Light blue
    CHSV(160, 255, 255), // Full blue
};

ColorPalette ice_cp(ice);