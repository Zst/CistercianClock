#ifndef DISPLAY_H
#define DISPLAY_H
#include <FastLED.h>

void displayAll(CRGB leds[], byte ledsCount, CRGB colors[], byte rightTopNumber, byte leftTopNumber, byte rightBottomNumber, byte leftBottomNumber);
void reset(CRGB leds[], int count);

#endif
