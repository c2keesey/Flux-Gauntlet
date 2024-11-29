#ifndef h_EFFECTSHANDLER_H
#define h_EFFECTSHANDLER_H

#include <vector>
#include "../shared/EffectsHandler.h"

class h_EffectsHandler : public EffectsHandler
{
private:
    std::vector<BaseEffect *> activeEffects = {};

protected:
    BaseEffect *getEffect(size_t index) override;
    size_t getEffectCount() const override;

public:
    h_EffectsHandler();

    void setupEffectLibrary();
    void addEffect(BaseEffect *effect);
    void setupTestLibrary();
    void triggerEffect(size_t index);
    void drawFrame() override;
};

#endif // h_EFFECTSHANDLER_H
