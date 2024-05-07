// #include <FastLED.h>
// #include "Eminate.h"
// #include "../h_effect_config.h"

// Eminate::Eminate(CRGBPalette256 palette) : BaseEffect(palette)
// {
// }
// void Eminate::trigger()
// {
// }

// void Eminate::update()
// {
//     for (int i = 0; i < BFL_CORNER; i++)
//     {
//         uint8_t hue = (-move + BFL_CORNER - i) % 255;
//         vleds[i] = ColorFromPalette(palette, hue);
//     }
//     for (int i = BFL_CORNER; i < BF_CENTER; i++)
//     {
//         uint8_t hue = (-move + i - BFL_CORNER) % 255;
//         vleds[i] = ColorFromPalette(palette, hue);
//     }
//     for (int i = BF_CENTER; i < BFR_CORNER; i++)
//     {
//         uint8_t hue = (-move + BFR_CORNER - i) % 255;
//         vleds[i] = ColorFromPalette(palette, hue);
//     }
//     for (int i = BFR_CORNER; i < NUM_LEDS; i++)
//     {
//         uint8_t hue = (-move + i - BFR_CORNER) % 255;
//         vleds[i] = ColorFromPalette(palette, hue);
//     }

//     move = (move + 1) % 255;
// }