#ifndef EMINATE_H
#define EMINATE_H

#include "../../shared/effects/BaseEffect.h"

class Eminate : public BaseEffect
{
public:
    Eminate(ColorPalette palette = rainbow_cp);

    virtual void update() override;
    virtual void trigger() override;

protected:
    int move = 0;
};

#endif // EMINATE_H
