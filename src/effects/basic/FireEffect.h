#pragma once
#include "effects/Effect.h"

class FireEffect : public Effect
{
public:
    FireEffect();
    void activate() override;
    void deactivate() override;
    void tick() override;
    void initialize(const JsonObject &json) override;
    void writeSettings(JsonObject &json) override;
    Effect* clone() const { return new FireEffect(*this); }

private:
    void generateLine();
    void shiftUp();
    void drawFrame(uint8_t pcnt);
};

