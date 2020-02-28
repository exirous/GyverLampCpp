#pragma once
#include "effects/noise/NoiseEffect.h"

class RainbowNoiseEffect : public NoiseEffect
{
public:
    RainbowNoiseEffect();
    Effect* clone() const { return new RainbowNoiseEffect(*this); }
};

