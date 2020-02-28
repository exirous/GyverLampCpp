#pragma once
#include "effects/Effect.h"

class HorizontalRainbowEffect : public Effect
{
public:
    HorizontalRainbowEffect();
    void tick() override;
    Effect* clone() const { return new HorizontalRainbowEffect(*this); }
};

