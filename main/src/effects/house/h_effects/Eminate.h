#ifndef EMINATE_H
#define EMINATE_H

#include "../../shared/effects/BaseEffect.h"

class Eminate : public BaseEffect
{
public:
    Eminate(CRGBPalette256 palette = RainbowColors_p);

    virtual void update() override;
    virtual void trigger() override;

protected:
    int move = 0;
};

#endif // EMINATE_H
