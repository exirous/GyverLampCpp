#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{

}

void Effect::Process() {
    tick();
    myMatrix->show();
}

void Effect::initialize(const JsonObject &json)
{
    update(json);
}

bool Effect::update(const JsonObject &json)
{
    bool shouldUpdate = false;
    if (json.containsKey(F("id"))) {
        settings.id = json[F("id")].as<String>();
        shouldUpdate = true;
    }
    if (json.containsKey(F("name"))) {
        settings.name = json[F("name")].as<String>();
        shouldUpdate = true;
    }
    if (json.containsKey(F("speed"))) {
        uint8_t speed = json[F("speed")];
        if (settings.speed != speed)
        {
            settings.speed = speed;
            shouldUpdate = true;
        }
    }
    if (json.containsKey(F("brightness"))) {
        uint8_t brightness = json[F("brightness")];
        if (settings.brightness != brightness)
        {
            settings.brightness = brightness;
            shouldUpdate = true;
        }
    }
    if (json.containsKey(F("scale"))) {
        uint16_t scale = json[F("scale")];
        if (settings.scale != scale)
        {
            settings.scale = scale;
            shouldUpdate = true;
        }
    }

    return shouldUpdate;
}

void Effect::writeSettings(JsonObject &json)
{

}