#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"
#include "../Rings.h"
#include <vector>

// TODO: Add branching
// TODO: Make points a Beam that will dissipate to the side when done
class Bolt
{
private:
    std::vector<int> points;
    bool done = false;
    Rings *rings;
    int curPoint;
    int curRing = 0;
    CHSV color;
    u8_t growUpdatePeriod = 15;
    u8_t flashUpdatePeriod = 20;
    u8_t dissipateUpdatePeriod = 20;
    unsigned long prevUpdateMillis = 0;
    u8_t flashCount = 0;
    enum state
    {
        GROWING,
        FLASHING,
        DISSIPATING
    } state;

public:
    Bolt(Rings *r, CHSV color) : rings(r), color(color)
    {
        curPoint = random(rings->getRingStart(0), rings->getRingEnd(0));
        points.push_back(curPoint);
        state = GROWING;
    }

    bool isDone() { return done; }

    void update()
    {
        if (done)
        {
            return;
        }

        int nextPoint;

        switch (state)
        {
        case GROWING:
            if (millis() - prevUpdateMillis < growUpdatePeriod)
            {
                return;
            }
            prevUpdateMillis = millis();
            color.v = qadd8(color.v, 10);
            nextPoint = curPoint + rings->getRingLength(curRing) + random(-2, 3);
            if (nextPoint > NUM_LEDS - 1)
            {
                state = FLASHING;
                break;
            }
            points.push_back(nextPoint);
            curPoint = nextPoint;
            curRing++;
            break;
        case FLASHING:
            if (flashCount < 4)
            {
                if (millis() - prevUpdateMillis < flashUpdatePeriod)
                {
                    return;
                }
                prevUpdateMillis = millis();
                if (flashCount % 2 == 0)
                {
                    color.v = 50;
                }
                else
                {
                    color.v = 255;
                }
                flashCount++;
            }
            else
            {
                state = DISSIPATING;
            }
            break;
        case DISSIPATING:
            if (millis() - prevUpdateMillis < dissipateUpdatePeriod)
            {
                return;
            }
            prevUpdateMillis = millis();
            color.v = qsub8(color.v, 10);
            if (color.v == 0)
            {
                done = true;
            }
            break;
        }
    }

    void drawBolt(CHSV *vleds)
    {
        if (done)
        {
            return;
        }
        for (auto &point : points)
        {
            vleds[point] = color;
        }
    }
};

class Lightning : public BaseEffect
{
private:
    std::vector<Bolt> bolts;
    Rings rings;

public:
    Lightning(ColorPalette pal = ice_cp) : BaseEffect(pal), rings(vleds)
    {
    }

    void trigger() override
    {
        CHSV color = palette.getRandomColor();
        bolts.push_back(Bolt(&rings, color));
    }

    void update() override
    {
        clearVleds(vleds);

        for (auto &bolt : bolts)
        {
            bolt.update();
            bolt.drawBolt(vleds);
        }

        // Remove done bolts
        for (auto it = bolts.begin(); it != bolts.end();)
        {
            if (it->isDone())
            {
                it = bolts.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

#endif // LIGHTNING_H