#include <Arduino.h>

#if defined(ESP32)
#include <SPIFFS.h>
#else
#include <FS.h>
#endif

#include "MyMatrix.h"
#include "EffectsManager.h"
#include "Settings.h"
#include "GyverTimer.h"
#include "WSocketClient.h"
#include "SunriseAlarm.h"

#include "effects/Effect.h"

namespace  {

#if defined(ESP32)
const uint8_t btnPin = 15;
#elif defined(SONOFF)
const uint8_t btnPin = 5;
#else
const uint8_t btnPin = D2;
#endif

int stepDirection = 1;
bool isHolding = false;

uint32_t logTimer = 0;
uint32_t logInterval = 10 * 1000;

bool setupMode = false;
bool connectFinished = false;

void printFlashInfo()
{
    uint32_t ideSize = ESP.getFlashChipSize();
    FlashMode_t ideMode = ESP.getFlashChipMode();

    Serial.printf_P(PSTR("Flash ide  size: %u bytes\n"), ideSize);
    Serial.printf_P(PSTR("Flash ide speed: %u Hz\n"), ESP.getFlashChipSpeed());
    Serial.print(F("Flash ide mode:  "));
    Serial.println((ideMode == FM_QIO ? F("QIO") : ideMode == FM_QOUT ? F("QOUT") : ideMode == FM_DIO ? F("DIO") : ideMode == FM_DOUT ? F("DOUT") : F("UNKNOWN")));

#if defined(ESP8266)
    uint32_t realSize = ESP.getFlashChipRealSize();
    Serial.printf_P(PSTR("Flash real id:   %08X\n"), ESP.getFlashChipId());
    Serial.printf_P(PSTR("Flash real size: %u bytes\n\n"), realSize);
    if (ideSize != realSize) {
      Serial.println(F("Flash Chip configuration wrong!"));
    } else {
      Serial.println(F("Flash Chip configuration ok."));
    }
#endif

    Serial.print(F("Sketch size: "));
    Serial.println(ESP.getSketchSize());
    Serial.print(F("Sketch free: "));
    Serial.println(ESP.getFreeSketchSpace());

#if defined(ESP32)
    Serial.print(F("Total heap: "));
    Serial.println(ESP.getHeapSize());
    Serial.print(F("Min free heap: "));
    Serial.println(ESP.getMinFreeHeap());
    Serial.print(F("Max alloc heap: "));
    Serial.println(ESP.getMaxAllocHeap());
#endif
}

void printFreeHeap()
{
    Serial.print(F("FreeHeap: "));
    Serial.println(ESP.getFreeHeap());
}

void setupSerial()
{
    Serial.begin(115200);
    Serial.println(F("\nHappy debugging!"));
    Serial.flush();
}

}

void setup() {
#if defined(ESP8266)
    ESP.wdtDisable();
    ESP.wdtEnable(0);
#endif

    setupSerial();
    printFlashInfo();
    printFreeHeap();

    if(!SPIFFS.begin()) {
        Serial.println(F("An Error has occurred while mounting SPIFFS"));
        return;
    }

    EffectsManager::Initialize();
    Settings::Initialize();
    MyMatrix::Initialize();
    WSocketClient::Initialize();
    SunriseAlarm::Initialize();

    effectsManager->ActivateEffect(mySettings->generalSettings.activeEffect);

    socketio->onConnected([](bool isConnected) {
        connectFinished = true;
        if (isConnected) {
            GyverTimer::Initialize();
        }
    });

    socketio->Connect();
}

void loop() {
#if defined(ESP8266)
    ESP.wdtFeed();
#endif
     socketio->loop();
     if (connectFinished)
     {
         GyverTimer::Process();
     }

    if (connectFinished && sunriseAlarm->IsInProgress())
    {
        sunriseAlarm->Process();
    }
    else
    {
        if (connectFinished)
            sunriseAlarm->CheckActivation();
        effectsManager->Process();
    }

    mySettings->Process();
}
