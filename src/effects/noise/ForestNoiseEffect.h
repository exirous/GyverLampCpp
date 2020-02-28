#pragma once
#include "effects/noise/NoiseEffect.h"

class ForestNoiseEffect : public NoiseEffect
{
public:
    ForestNoiseEffect();
    Effect* clone() const { return new ForestNoiseEffect(*this); }
};

