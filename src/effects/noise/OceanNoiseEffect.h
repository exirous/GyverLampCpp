#pragma once
#include "effects/noise/NoiseEffect.h"

class OceanNoiseEffect : public NoiseEffect
{
public:
    OceanNoiseEffect();
    Effect* clone() const { return new OceanNoiseEffect(*this); }
};

