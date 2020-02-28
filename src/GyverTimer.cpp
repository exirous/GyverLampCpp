#include "GyverTimer.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Settings.h"

namespace  {

int updateInterval = 60 * 1000 * 5; // 1 min

WiFiUDP *ntpUDP = nullptr;
NTPClient *timeClient = nullptr;

unsigned long hours = 0;
String hoursString = "88";
unsigned long minutes = 0;
String minutesString = "88";
unsigned long seconds = 0;
String secondsString = "88";

} // namespace

void GyverTimer::Initialize()
{
    ntpUDP = new WiFiUDP;

    timeClient = new NTPClient(*ntpUDP,
                               mySettings->connectionSettings.ntpServer.c_str(),
                               mySettings->connectionSettings.ntpOffset,
                               updateInterval);
    timeClient->begin();

    Serial.printf_P(PSTR("Initializing GyverTimer: %s, offset: %d\n"),
                    mySettings->connectionSettings.ntpServer.c_str(),
                    mySettings->connectionSettings.ntpOffset);
}

void GyverTimer::Process()
{
    if (!timeClient) {
        return;
    }

    timeClient->update();
    ReadTime();
}

void GyverTimer::SetInterval(uint32_t timerInterval)
{
    if (!timeClient) {
        return;
    }
    timeClient->setUpdateInterval(timerInterval);
}

void GyverTimer::ForceUpdate()
{
    if (!timeClient) {
        return;
    }

    timeClient->forceUpdate();
}

void GyverTimer::ReadTime()
{
    if (!timeClient) {
        return;
    }

    const unsigned long rawTime = timeClient->getEpochTime();
    hours = (rawTime % 86400L) / 3600;
    hoursString = hours < 10 ? String(0) + String(hours) : String(hours);

    minutes = (rawTime % 3600) / 60;
    minutesString = minutes < 10 ? String(0) + String(minutes) : String(minutes);

    seconds = rawTime % 60;
    secondsString = seconds < 10 ? String(0) + String(seconds) : String(seconds);
}

boolean GyverTimer::IsZeroSeconds() 
{
    return timeClient->getSeconds() == 0;
}

boolean GyverTimer::UpdateTime()
{
    return timeClient->update();
}


uint8_t GyverTimer::GetDayOfWeek() 
{
    int8_t day = timeClient->getDay() - 1;
    if (day == -1) day = 6;
    return day;
}

int GyverTimer::GetCurrentDayMinutes()
{
    return timeClient->getHours() * 60 + timeClient->getMinutes();
}

int GyverTimer::GetSeconds()
{
    return timeClient->getSeconds();
}

String GyverTimer::Time()
{
    return timeClient->getFormattedTime();
}


String GyverTimer::Hours()
{
    return hoursString;
}

String GyverTimer::Minutes()
{
    return minutesString;
}

String GyverTimer::Seconds()
{
    return secondsString;
}
