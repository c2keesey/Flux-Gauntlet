// Twinkle.h

#ifndef FIREWORKS_H
#define FIREWORKS_H

#include "BaseEffect.h"
#include "../../../config/config.h"
#include <vector>
#include "../EffectHelpers.h"

struct Particle
{
    float pos;
    CRGB color;
    float speed;
    Particle(float p, CRGB c, float s) : pos(p), color(c), speed(s) {}
};

class Firework
{
private:
    int pos;
    unsigned long lastMove = 0;
    unsigned long lastFade = 0;
    float deceleration;
    float explosionStrength;
    int numParticleSpread;

    std::vector<Particle> particles;

public:
    Firework(int pos, float deceleration = 0.01f, float explosionStrength = 25.0f, int numParticleSpread = 15, int nParticles = 0)
    {
        this->deceleration = deceleration;
        this->pos = pos;
        this->explosionStrength = explosionStrength; // TODO: make this a function and validate
        uint8_t hueSpread = random8(50, 255);
        uint8_t hueStart = random8();
        uint8_t hueEnd = (hueStart + hueSpread) % 255;
        int numParticles = nParticles > 0 ? nParticles : (5, 5 + numParticleSpread);

        for (int i = 0; i < numParticles; i++)
        {
            particles.push_back(Particle(pos, CHSV(random8(hueStart, hueEnd), 255, 255), randomAbsRange(10, 2)));
        }
    }

    void update()
    {
        if (millis() - lastMove > 10)
        {
            lastMove = millis();

            for (auto part = particles.begin(); part != particles.end();)
            {
                part->pos += part->speed / explosionStrength;
                if (part->pos < 0 || part->pos > NUM_LEDS - 1)
                {
                    part = particles.erase(part);
                    continue;
                }
                if (part->speed < 0)
                {
                    part->speed += deceleration;
                }
                else
                {
                    part->speed -= deceleration;
                }
                ++part;
            }
        }
        if (millis() - lastFade > 10)
        {
            lastFade = millis();
            for (auto part = particles.begin(); part != particles.end();)
            {
                if (part->speed < deceleration && part->speed > -deceleration)
                {
                    part->color.fadeToBlackBy(10);
                }
                else
                {

                    part->color.fadeToBlackBy(2);
                }
                if (part->color.getLuma() < 1)
                {
                    part = particles.erase(part);
                }
                else
                {
                    ++part;
                }
            }
        }
    }

    void drawFirework(CRGB *vleds)
    {
        for (auto part = particles.begin(); part != particles.end();)
        {
            if (part->pos < 0 || part->pos > NUM_LEDS - 1)
            {
                part = particles.erase(part);
            }
            else
            {
                drawPrecise(part->pos, 1, part->color, vleds);
                ++part;
            }
        }
    }

    size_t getNumParticles()
    {
        return particles.size();
    }
};

class FireworkShow : public BaseEffect
{
private:
    unsigned long fadeMillis = 0;
    std::vector<Firework> fireworks = {};
    unsigned long triggerMillis = 0;
    float explosionStrength;
    float deceleration;
    int fireworkOffset = 50;

public:
    FireworkShow(int speed = 20, CRGBPalette256 pal = DEFAULT_PALETTE, float deceleration = 0.01f, float explosionStrength = 25.0f)
        : BaseEffect(pal), explosionStrength(explosionStrength), deceleration(deceleration)
    {
        this->speed = speed;
    }

    void trigger() override
    {
        if (random(100) == 0)
        {
            fireworks.push_back(Firework(random(fireworkOffset, NUM_LEDS - fireworkOffset), randomVariance(deceleration, 1), 15.0f, 50, 200));
        }
        else if (random(20) == 0)
        {
            fireworks.push_back(Firework(random(fireworkOffset, NUM_LEDS - fireworkOffset), randomVariance(deceleration, 1), 25.0f, 50, 50));
        }
        else
        {
            fireworks.push_back(Firework(random(fireworkOffset, NUM_LEDS - fireworkOffset), randomVariance(deceleration, 1), randomVariance(explosionStrength, 25)));
        }
    }

    void update() override
    {
        clearVleds(vleds);

        for (auto firework = fireworks.begin(); firework != fireworks.end();)
        {
            firework->update();
            firework->drawFirework(vleds);
            if (firework->getNumParticles() == 0)
            {
                firework = fireworks.erase(firework);
            }
            else
            {
                ++firework;
            }
        }
    }
};

#endif // FIREWORKS_H
