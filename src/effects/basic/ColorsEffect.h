#pragma once
#include "effects/Effect.h"

class ColorsEffect : public Effect
{
public:
    ColorsEffect();
    void tick() override;
    Effect* clone() const { return new ColorsEffect(*this); }
};

