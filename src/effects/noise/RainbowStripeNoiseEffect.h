#pragma once
#include "effects/noise/NoiseEffect.h"

class RainbowStripeNoiseEffect : public NoiseEffect
{
public:
    RainbowStripeNoiseEffect();
    Effect* clone() const { return new RainbowStripeNoiseEffect(*this); }
};

