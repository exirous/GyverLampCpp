#pragma once
#include "effects/Effect.h"

class MatrixEffect : public Effect
{
public:
    MatrixEffect();
    void tick() override;
    Effect* clone() const { return new MatrixEffect(*this); }
};

