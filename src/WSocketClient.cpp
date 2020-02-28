#include "WSocketClient.h"

#include "Settings.h"
#include <SocketIoClient.h>
#include <ESPReactWifiManager.h>
#include "EffectsManager.h"
#include "MyMatrix.h"
#include "SunriseAlarm.h"
#include "effects/Effect.h"

namespace
{
WSocketClient *instance = nullptr;
ESPReactWifiManager *wifiManager = nullptr;
SocketIoClient webSocket;
void (*onConnectedCallback)(bool) = nullptr;

void socketConnected(const char *payload, size_t length) {
    Serial.println(F("Connected to websocket"));
    webSocket.emit("lamp", mySettings->GetConfigBuffer());
}

void socketToggle(const char *payload, size_t length) {
    boolean shouldTurnOn;
    if (strcmp(payload,"ON") == 0)
        shouldTurnOn = true;
    else
        shouldTurnOn = false;

    mySettings->generalSettings.working = shouldTurnOn;
}

void socketActiveEffect(const char *payload, size_t length) {
        const int index = String(payload).toInt();
        effectsManager->ChangeEffect(static_cast<uint8_t>(index));
}

void socketEffectSettings(const char *payload, size_t length) {
        DynamicJsonDocument doc(512);
        deserializeJson(doc, payload);
        const JsonObject effect = doc[F("data")];
        effectsManager->UpdateCurrentSettings(effect);
}

void socketAlarmSettings(const char *payload, size_t length) {
        sunriseAlarm->ProcessConfig(payload);
}

}

WSocketClient *WSocketClient::Instance()
{
    return instance;
}

void WSocketClient::Initialize()
{
    if (instance) {
        return;
    }

#if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
#endif  

    Serial.println(F("Initializing SocketClient"));
    instance = new WSocketClient();
}

void WSocketClient::Connect()
{
    Serial.println(F("Starting SocketClient"));
    wifiManager = new ESPReactWifiManager();
    wifiManager->connect("", "", "");
    wifiManager->setFallbackToAp(false);

    webSocket.on("connect", socketConnected);
    webSocket.on("toggle", socketToggle);
    webSocket.on("activeEffect", socketActiveEffect);
    webSocket.on("effectSetting", socketEffectSettings);
    webSocket.on("alarms", socketAlarmSettings);

    wifiManager->onFinished([](bool isAPMode) {
        Serial.println(F("Connected to wifi"));
        webSocket.begin("smarthome.vihnevich.club"); 
        if (onConnectedCallback) {
            onConnectedCallback(true);
        }
    });    
}

void WSocketClient::loop()
{
    wifiManager->loop();
    webSocket.loop();
}

void WSocketClient::update()
{
    //sendState();
}

void WSocketClient::onConnected(void (*func)(bool))
{
    onConnectedCallback = func;
}


WSocketClient::WSocketClient()
{

}