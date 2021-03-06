#pragma once
#include "MyMatrix.h"
#include "Settings.h"
#define ARDUINOJSON_ENABLE_PROGMEM 1
#include <ArduinoJson.h>

class Effect
{
public:
    Effect();
    virtual ~Effect();
    void Process();

    virtual void activate() {}
    virtual void deactivate() {}

    virtual void initialize(const JsonObject &json);
    virtual bool update(const JsonObject &json);
    virtual void writeSettings(JsonObject &json);

    virtual void tick() = 0;

    virtual Effect* clone() const = 0;

    Settings::EffectSettings settings;
};
