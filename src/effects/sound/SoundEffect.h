#pragma once
#include "effects/Effect.h"

class SoundEffect : public Effect
{
public:
    SoundEffect();
    virtual void tick() override;
    void initialize(const JsonObject &json) override;
    void writeSettings(JsonObject &json) override;
    Effect* clone() const { return new SoundEffect(*this); }

private:
    void displayBand(int band, int dsize);
    byte getBand(int i);
    void setBandwidth();
};
