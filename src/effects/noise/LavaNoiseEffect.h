#pragma once
#include "effects/noise/NoiseEffect.h"

class LavaNoiseEffect : public NoiseEffect
{
public:
    LavaNoiseEffect();
    Effect* clone() const { return new LavaNoiseEffect(*this); }
};

