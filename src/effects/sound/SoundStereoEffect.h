#pragma once
#include "effects/Effect.h"

class SoundStereoEffect : public Effect
{
public:
    SoundStereoEffect();
    virtual void tick() override;
    Effect* clone() const { return new SoundStereoEffect(*this); }

private:
    void displayLBand(int band);
    void displayRBand(int band);
    byte getLBand(int i);
    byte getRBand(int i);
    void setBandwidth();
};
