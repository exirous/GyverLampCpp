#pragma once
#include "effects/Effect.h"

class ColorEffect : public Effect
{
public:
    ColorEffect();
    void tick() override;
    void initialize(const JsonObject &json) override;
    void writeSettings(JsonObject &json) override;
    Effect* clone() const { return new ColorEffect(*this); }
};

