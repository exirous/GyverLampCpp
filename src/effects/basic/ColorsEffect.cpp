#include "ColorsEffect.h"

namespace  {

uint8_t hue = 0;

} // namespace

ColorsEffect::ColorsEffect()
{
}

void ColorsEffect::tick()
{
    hue += settings.scale;
    myMatrix->fill(CHSV(hue, 255, 255));
}
