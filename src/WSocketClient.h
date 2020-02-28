#pragma once
#include <Arduino.h>
#define ARDUINOJSON_ENABLE_PROGMEM 1
#include <ArduinoJson.h>
#include <PubSubClient.h>

#define socketio WSocketClient::Instance()

class WSocketClient
{
public:
    static WSocketClient *Instance();
    static void Initialize();
    static void Connect();

    void loop();
    void update();
    void onConnected(void (*func)(bool));

protected:
    WSocketClient();
};

