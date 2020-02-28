#pragma once
#include "effects/Effect.h"

class DiagonalRainbowEffect : public Effect
{
public:
    DiagonalRainbowEffect();
    void tick() override;
    Effect* clone() const { return new DiagonalRainbowEffect(*this); }
};

