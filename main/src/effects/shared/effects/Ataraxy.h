
// // Ataraxy.h

// #ifndef ATARAXY_H
// #define ATARAXY_H

// #include "BaseEffect.h"
// #include <vector>
// #include "../EffectHelpers.h"
// #include <FastLED.h>

// const int ORB_COUNT = 100;
// const int MIN_ORB_VAL = 90;
// const int MAX_ORB_VAL = 180;
// const int MAX_ORB_SAT = 255;
// const int MIN_ORB_SAT = 235;
// // Want high saturation <200 but val can be low
// // Mid sat low val is nice too around 200 50 before goes red
// const int spread = 3;
// const float MIN_ORB_VEL = 0.0005f;
// const float MAX_ORB_VEL = 0.02f;
// const int MIN_ORB_SIZE = 1;
// const int MAX_ORB_SIZE = 4;
// const int MIN_ORB_LIFE = 30;
// const int MAX_ORB_LIFE = 60;
// const int MIN_HUE = 20;
// const int MAX_HUE = 25;

// struct Orb
// {
//     float pos;
//     int size;
//     CHSV color;
//     CRGB baseColor;
//     uint8_t scale = 255;
//     float velocity;
//     uint8_t distance;
//     bool pulseIncreasing = true;
//     int lifespan; // in seconds
//     Orb(float p, int s, CHSV c, CRGB bc, float v, uint8_t d, int l) : pos(p), size(s), color(c), baseColor(bc), velocity(v), distance(d), lifespan(l) {}
// };

// class Ataraxy : public BaseEffect
// {
// private:
//     std::vector<Orb> orbs;
//     unsigned long prevDecTime = 0;
//     unsigned long prevUpdatePulse = 0;
//     int updatePulseFrequncy = 50;

// public:
//     Ataraxy(CRGBPalette256 pal = DEFAULT_PALETTE)
//     {
//         palette = pal;
//         triggerDelay = 500;
//         for (int i = 0; i < ORB_COUNT; i++)
//         {
//             orbs.push_back(createRandomOrb(i * (MIN_ORB_LIFE + MAX_ORB_LIFE) / 2));
//         }
//     }

//     void trigger() override
//     {
//         orbs.push_back(createRandomOrb(random(MIN_ORB_LIFE, MAX_ORB_LIFE)));
//     }

//     Orb createRandomOrb(int life, int val = -1)
//     {
//         if (val == -1)
//         {
//             val = random(MIN_ORB_VAL, MAX_ORB_VAL);
//         }
//         CHSV color = CHSV(random(MIN_HUE, MAX_HUE), random(MIN_ORB_SAT, MAX_ORB_SAT), val);
//         CRGB baseColor = CRGB(color);
//         float pos = random(0, NUM_LEDS);
//         float vel = random(MIN_ORB_VEL * 10000, MAX_ORB_VEL * 10000) / 20000.0f;
//         vel = random(2) == 0 ? -vel : vel;
//         int size = random(MIN_ORB_SIZE, MAX_ORB_SIZE);
//         int lifespan = life;
//         const Orb rOrb = Orb(pos, size, color, baseColor, 0, lifespan);
//         return rOrb;
//     }

//     CRGB getOrbColor(Orb *orb)
//     {
//         return hsv
//     }

//     void update() override
//     {
//         clearVleds(vleds);

//         if (millis() - prevDecTime > 1000)
//         {
//             prevDecTime = millis();
//             for (auto orb = orbs.begin(); orb != orbs.end(); orb++)
//             {
//                 orb->lifespan--;
//             }
//         }
//         if (millis() - prevUpdatePulse > updatePulseFrequncy)
//         {
//             prevUpdatePulse = millis();
//             for (auto orb = orbs.begin(); orb != orbs.end(); orb++)
//             {
//                 if (orb->pulseIncreasing)
//                 {
//                     // TODO: change everything to use crgb then can use nscale8_video
//                     orb->baseColor.nscale8_video(orb->scale);
//                     orb->color = CHSV(orb->baseColor);
//                     orb->scale++;
//                 }
//                 else
//                 {
//                     orb->baseColor.nscale8_video(orb->scale);
//                     orb->color = CHSV(orb->baseColor);
//                     orb->scale--;
//                 }
//                 if (orb->color.val >= MAX_ORB_VAL)
//                 {
//                     orb->pulseIncreasing = false;
//                 }
//                 if (orb->color.val <= MIN_ORB_VAL)
//                 {
//                     orb->pulseIncreasing = true;
//                 }
//             }
//         }

//         for (auto orb = orbs.begin(); orb != orbs.end();)
//         {
//             if (orb->lifespan < 0 || orb->pos < 0 || orb->pos > NUM_LEDS - 1)
//             {
//                 orbs.erase(orb);
//                 orbs.push_back(createRandomOrb(random(MIN_ORB_LIFE, MAX_ORB_LIFE), 0));
//                 orb++;
//             }
//             else
//             {
//                 orb->pos += orb->velocity;
//                 orb++;
//             }
//         }
//         drawOrbs();
//     }

//     void drawOrbs()
//     {
//         for (auto orb = orbs.begin(); orb != orbs.end();)
//         {
//             drawOrb(&*orb);
//             orb++;
//         }
//     }

//     void drawOrb(Orb *orb)
//     {
//         drawPrecise(orb->pos, orb->size, orb->color, vleds);
//     }

//     void drawDistance(Orb *orb)
//     {
//     }
// };

// #endif // ATARAXY_H
