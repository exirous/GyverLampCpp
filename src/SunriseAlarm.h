#pragma once
#include <Arduino.h>
#define ARDUINOJSON_ENABLE_PROGMEM 1
#include <ArduinoJson.h>

#define sunriseAlarm SunriseAlarm::Instance()

class SunriseAlarm
{
public:

    struct AlarmSetting {
        bool IsOn = false;
        int Time = 420;
    };

    static SunriseAlarm *Instance();
    static void Initialize();
    
    boolean IsInProgress();
    void CheckActivation();
    void ForceActivationCheck();
    void Process();

    void ProcessConfig(const String &message);
    void SaveLater();
    void Save();
    void BuildJson(JsonObject &root);
    String GetConfigBuffer();

protected:
    SunriseAlarm();
};

