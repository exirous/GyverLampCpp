#pragma once
#include "effects/noise/NoiseEffect.h"

class CloudNoiseEffect : public NoiseEffect
{
public:
    CloudNoiseEffect();
    Effect* clone() const { return new CloudNoiseEffect(*this); }
};

