#include "DawnEffect.h"


namespace{
    CRGB dawnColor;
    const int DAWN_BRIGHT = 200;
}

DawnEffect::DawnEffect()
{
}

void DawnEffect::tick()
{
    int dawnPosition = settings.scale;
    uint8_t height = mySettings->matrixSettings.height;
    uint8_t width = mySettings->matrixSettings.width;

    long H = map(dawnPosition, 0, 255, 10, 35);
    long S = map(dawnPosition, 0, 255, 255, 170);
    long V = map(dawnPosition, 0, 255, 10, DAWN_BRIGHT);
    dawnColor = CHSV(H,S,V);

    for (int16_t y = (height - 1); y >= 0; y--) {
        for (int16_t x = (width - 1); x >= 0; x--) {
            if (x > 0)
                myMatrix->drawPixelXY(x, y, myMatrix->getPixColorXY(x - 1, y));
            else if (y > 0)
                myMatrix->drawPixelXY(x, y, myMatrix->getPixColorXY((width - 1), y - 1));
        }
    }

    myMatrix->drawPixelXY(0, 0, dawnColor);
}

void DawnEffect::initialize(const JsonObject &json)
{
    Effect::initialize(json);
}
