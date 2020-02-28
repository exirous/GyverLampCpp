#pragma once
#include <Arduino.h>

class GyverTimer
{
public:
    static void Initialize();
    static void Process();
    static void SetInterval(uint32_t timerInterval);
    static void ForceUpdate();
    static void ReadTime();
    static int  GetCurrentDayMinutes();
    static uint8_t GetDayOfWeek();
    static boolean IsZeroSeconds();
    static boolean UpdateTime();
    static int GetSeconds();
    
    static String Hours();
    static String Minutes();
    static String Seconds();
    static String Time();
};

