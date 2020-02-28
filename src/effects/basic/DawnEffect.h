#pragma once
#include "effects/Effect.h"

class DawnEffect : public Effect
{
public:
    DawnEffect();
    void tick() override;
    void initialize(const JsonObject &json) override;
    Effect* clone() const { return new DawnEffect(*this); }

private:
};

