#pragma once
#include "effects/Effect.h"

class VerticalRainbowEffect : public Effect
{
public:
    VerticalRainbowEffect();
    void tick() override;
    Effect* clone() const { return new VerticalRainbowEffect(*this); }
};

