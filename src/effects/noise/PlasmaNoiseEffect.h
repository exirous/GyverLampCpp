#pragma once
#include "effects/noise/NoiseEffect.h"

class PlasmaNoiseEffect : public NoiseEffect
{
public:
    PlasmaNoiseEffect();
    Effect* clone() const { return new PlasmaNoiseEffect(*this); }
};

