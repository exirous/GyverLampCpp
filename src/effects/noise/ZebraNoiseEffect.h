#pragma once
#include "effects/noise/NoiseEffect.h"

class ZebraNoiseEffect : public NoiseEffect
{
public:
    ZebraNoiseEffect();
    Effect* clone() const { return new ZebraNoiseEffect(*this); }
};

