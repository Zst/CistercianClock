#ifndef DISPLAY_H
#define DISPLAY_H
#include <FastLED.h>

void displayAll(CRGB leds[], CRGB colors[], byte rightTopNumber, byte leftTopNumber, byte rightBottomNumber, byte leftBottomNumber);
void lightRange(CRGB leds[], CRGB color, int start, int count);
void reset(CRGB leds[], int count);

#endif
