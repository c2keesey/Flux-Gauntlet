// #include <FastLED.h>
// #include "Sparks.h"
// #include "../h_effect_config.h"

// Sparks::Sparks(ColorPalette palette, int rate, int halfLife) : BaseEffect(palette), rate(rate), halfLife(halfLife)
// {
//     for (int i = 0; i < 50; i++)
//     {
//         Spark spark;
//         spark.pos = random(NUM_LEDS);
//         spark.vel = random(4) - 2;
//         if (spark.vel == 0)
//         {
//             spark.vel = 1;
//         }
//         spark.color = ColorFromPalette(palette, random(255));
//         sparkVector.push_back(spark);
//     }
// }
// void Sparks::trigger()
// {
// }

// void Sparks::update()
// {
//     for (int i = 0; i < NUM_LEDS; i++)
//     {
//         vleds[i] = CRGB::Black;
//     }
//     for (auto &spark : sparkVector)
//     {
//         vleds[spark.pos % NUM_LEDS] = spark.color;
//         spark.pos = (spark.vel + spark.pos) % NUM_LEDS;
//         if (spark.pos < 0)
//         {
//             spark.pos += NUM_LEDS; // Neg modulo doesnt work on this controller
//         }
//     }
// }