#include "SunriseAlarm.h"
#include "GyverTimer.h"
#include "EffectsManager.h"
#if defined(ESP32)
#include <SPIFFS.h>
#else
#include <FS.h>
#endif

namespace
{
SunriseAlarm *instance = nullptr;
boolean dawnAlarmActive = false;
boolean timeAquired = false;
const int DAWN_OFFSET = 5;
const int DAWN_COOLDOWN = 5;

const size_t jsonSerializeSize = 512 * 12;
bool settingsChanged = false;
uint32_t settingsSaveTimer = 0;
uint32_t settingsSaveInterval = 3000;
const char* settingsFileName PROGMEM = "/alarmSettings.json";
unsigned long lastFrameMillis = 0;
unsigned long lastMillis = 0;

SunriseAlarm::AlarmSetting alarms[7];
unsigned long lastActivationCheck = 0;
}

SunriseAlarm *SunriseAlarm::Instance()
{
    return instance;
}

void SunriseAlarm::Initialize()
{
    if (instance) {
        return;
    }  

    Serial.println(F("Initializing Sunrise alarm"));
    instance = new SunriseAlarm();
}

boolean SunriseAlarm::IsInProgress()
{
    return dawnAlarmActive;
}

void SunriseAlarm::Process()
{    
    unsigned long now = millis();

    const int dayMinutes = GyverTimer::GetCurrentDayMinutes();    
    const int daySeconds = GyverTimer::GetSeconds();    
    const uint8_t dayOfWeek = GyverTimer::GetDayOfWeek();
    
    if ((now - lastMillis) < 120)
        return;
    lastMillis = now;

    const long nowSeconds = (dayMinutes * 60) + daySeconds;
    const int alarmTimeSeconds = (alarms[dayOfWeek].Time - DAWN_OFFSET) * 60;
    int dawnPosition = (float)255 * (float)((nowSeconds - alarmTimeSeconds) / (float)(DAWN_OFFSET * 60));
    dawnPosition = constrain(dawnPosition, 0, 255);
    effectsManager->ForceEffect(26, 255, 120, dawnPosition);
    CheckActivation();
    if (!dawnAlarmActive)
        effectsManager->ClearForcedEffect();
    else
        effectsManager->ProcessForcedEffect();
}

void SunriseAlarm::CheckActivation()
{
    if (!GyverTimer::UpdateTime())
       return;

    if (!GyverTimer::IsZeroSeconds() && timeAquired)
       return;
    timeAquired = true;   

    int activationCheckTimeDiff = millis() - lastActivationCheck;
    if (activationCheckTimeDiff < 1000)
        return;
    lastActivationCheck = millis();
    ForceActivationCheck();
}

void SunriseAlarm::ForceActivationCheck()
{
    Serial.print("Alarm check: ");
    Serial.println(GyverTimer::Time());

    const uint8_t dayOfWeek = GyverTimer::GetDayOfWeek();
    const int dayMinutes = GyverTimer::GetCurrentDayMinutes();
    
     // TODO: Also consider 00:00 and 23:59;
     if (alarms[dayOfWeek].IsOn)
        dawnAlarmActive = (dayMinutes >= (alarms[dayOfWeek].Time - DAWN_OFFSET) && dayMinutes < (alarms[dayOfWeek].Time + DAWN_COOLDOWN));
     else
        dawnAlarmActive = false;

     if (!dawnAlarmActive)
         effectsManager->ClearForcedEffect();
    
    Serial.println(dawnAlarmActive ? "Alarm is active" : "Alarm is not active");      
}

void SunriseAlarm::SaveLater()
{
    settingsChanged = true;
    settingsSaveTimer = millis();
}

void SunriseAlarm::Save()
{
    Serial.println(F("Openning alarm spiffs.."));
    File file = SPIFFS.open(settingsFileName, "w");
    if (!file) {
        Serial.println(F("Error opening alarm settings file from SPIFFS!"));
        return;
    }
    DynamicJsonDocument json(1024 * 6);
    JsonObject root = json.to<JsonObject>();
    Serial.println(F("building json"));
    BuildJson(root);

    Serial.println(F("serializing json.."));

    if (serializeJson(json, file) == 0) {
        Serial.println(F("Failed to write to file"));
    }

    if (file) {
        Serial.println(F("closng file"));
        file.close();
    }
}

String SunriseAlarm::GetConfigBuffer()
{
    DynamicJsonDocument json(1024 * 6);
    JsonObject root = json.to<JsonObject>();
    Serial.println(F("building json"));
    BuildJson(root);

    Serial.println(F("serializing json.."));
    String buffer;
    if (serializeJson(json, buffer) == 0) {
        Serial.println(F("Failed to write to buffer"));
    }
    return buffer;
}

void SunriseAlarm::ProcessConfig(const String &message)
{
    DynamicJsonDocument doc(512);
    deserializeJson(doc, message);

    for (uint8_t i = 0; i < 7; i++) 
    {
        alarms[i].IsOn = doc[F("alarms")][i][F("IsOn")];
        alarms[i].Time = doc[F("alarms")][i][F("Time")];
        Serial.print("Set alarm: ");
        Serial.print(i);
        Serial.print(" as ");
        Serial.print(alarms[i].IsOn ? "On" : "Off");
        Serial.print(" at ");
        Serial.println(alarms[i].Time);
    }

    SaveLater();
    ForceActivationCheck();
}

void SunriseAlarm::BuildJson(JsonObject &root)
{
    JsonArray alarmsJson = root.createNestedArray(F("alarms"));
    for (uint8_t i = 0; i < 7; i++) 
    {
        JsonObject alarmJson = alarmsJson.createNestedObject();
        alarmJson[F("IsOn")] = alarms[i].IsOn;
        alarmJson[F("Time")] = alarms[i].Time;
    }
}

SunriseAlarm::SunriseAlarm()
{

}