#pragma once
#include "effects/Effect.h"

class SparklesEffect : public Effect
{
public:
    SparklesEffect();
    void tick() override;
    Effect* clone() const { return new SparklesEffect(*this); }

private:
    void fader(uint8_t step);
};

