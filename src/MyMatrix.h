#pragma once

#if defined(ESP8266)
#define FASTLED_ESP8266_RAW_PIN_ORDER
//#define FASTLED_INTERRUPT_RETRY_COUNT 0
//#define FASTLED_ALLOW_INTERRUPTS 0
#endif

#include <Arduino.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <FastLED_NeoMatrix.h>

#define myMatrix MyMatrix::Instance()

class MyMatrix : public FastLED_NeoMatrix
{
public:
    static MyMatrix *Instance();
    static void Initialize();

    static uint8_t GetRotation();

    void setCurrentLimit(uint32_t maxCurrent);

    void matrixTest();

    void clear(bool shouldShow = false);
    void fill(CRGB color, bool shouldShow = false);
    void fillProgress(double progress);
    void setLed(uint16_t index, CRGB color);
    void fadeToBlackBy(uint16_t index, uint8_t step);

    uint16_t getPixelNumberXY(uint8_t x, uint8_t y);

    void drawPix(uint16_t number, CRGB color);
    void drawPixelXY(uint8_t x, uint8_t y, CRGB color);
    void drawLineXY(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, CRGB color);


    CRGB getPixColor(uint16_t number);
    CRGB getPixColorXY(uint8_t x, uint8_t y);

    void fillRectXY(uint8_t x, uint8_t y, uint8_t w, uint8_t h, CRGB color);

    void fadePixelXY(uint8_t x, uint8_t y, uint8_t step);

protected:
    MyMatrix(CRGB *leds, uint8_t w, uint8_t h, uint8_t matrixType);
};
