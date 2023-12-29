#ifndef h_EFFECTSHANDLER_H
#define h_EFFECTSHANDLER_H

#include "../shared/EffectsHandler.h"

class h_EffectsHandler : public EffectsHandler
{
public:
    h_EffectsHandler();

    void setupEffectLibrary() override;
};

#endif // h_EFFECTSHANDLER_H
