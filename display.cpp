#include "display.h"

#define SEGMENTS_COUNT 5
#define LEDS_IN_SEGMENT 4

enum Segment { outer_line, inner_line, primary_diagonal, secondary_diagonal, vertical };


/*
 * Leds layout
 * 
 * 57 53 49 33 45 41 37
 * 56 52 48 32 44 40 36
 * 55 51 47 31 43 39 35 
 * 54 50 46 30 42 38 34
 *          29
 *          28 
 * 23 19 15 27 11 07 03
 * 22 18 14 26 10 06 02
 * 21 17 13 25 09 05 01
 * 20 16 12 24 08 04 00 
 */
byte led_map[4][SEGMENTS_COUNT][LEDS_IN_SEGMENT] = {
  // top right, first position
  { 
    /* outer_line         */ {45, 41, 200, 200},
    /* inner_line         */ {42, 38, 200, 200},
    /* primary_diagonal   */ {44, 39, 200, 200},
    /* secondary_diagonal */ {43, 40, 200, 200},
    /* vertical           */ {34, 35, 36, 37},
  },
  // top left, second position
  { 
    /* outer_line         */ {53, 49, 200, 200},
    /* inner_line         */ {50, 46, 200, 200},
    /* primary_diagonal   */ {48, 51, 200, 200},
    /* secondary_diagonal */ {52, 47, 200, 200},
    /* vertical           */ {54, 55, 56, 57},
  },
  // bottom right, third position
  { 
    /* outer_line         */ {8, 4, 200, 200},
    /* inner_line         */ {11, 7, 200, 200},
    /* primary_diagonal   */ {9, 6, 200, 200},
    /* secondary_diagonal */ {10, 5, 200, 200},
    /* vertical           */ {0, 1, 2, 3},
  },
  // bottom left, fourth position
  { 
    /* outer_line         */ {16, 12, 200, 200},
    /* inner_line         */ {19, 15, 200, 200},
    /* primary_diagonal   */ {13, 18, 200, 200},
    /* secondary_diagonal */ {17, 14, 200, 200},
    /* vertical           */ {20, 21, 22, 23},
  }
};


void lightRange(CRGB leds[], CRGB color, int start, int count) {
  for (int i = 0; i < count; i++) {
    leds[start + i] = color;
  }
}

void reset(CRGB leds[], int count) {
  for(int i = 0; i < count; i++) {
    leds[i] = CRGB::Black;
  }
}

void lightSegment(CRGB leds[], byte ledsCount, CRGB color, byte numberIndex, Segment segment) {
  for(int i = 0; i < LEDS_IN_SEGMENT; i++) {
    int idx = led_map[numberIndex][segment][i];
    if (idx < ledsCount) 
      leds[idx] = color;
  }
}

void lightNumber(CRGB leds[], byte ledsCount, CRGB colors[], byte number, byte numberIndex) {
  int num = number % 10;
  CRGB color = colors[number / 10];
  switch (num) {
    case 1: 
      lightSegment(leds, ledsCount, color, numberIndex, outer_line);
      break;
    case 2: 
      lightSegment(leds, ledsCount, color, numberIndex, inner_line);
      break;
    case 3: 
      lightSegment(leds, ledsCount, color, numberIndex, primary_diagonal);
      break;
    case 4: 
      lightSegment(leds, ledsCount, color, numberIndex, secondary_diagonal);
      break;    
    case 5: 
      lightSegment(leds, ledsCount, color, numberIndex, outer_line);
      lightSegment(leds, ledsCount, color, numberIndex, secondary_diagonal);
      break;
    case 6: 
      lightSegment(leds, ledsCount, color, numberIndex, vertical);
      break;
    case 7: 
      lightSegment(leds, ledsCount, color, numberIndex, outer_line);
      lightSegment(leds, ledsCount, color, numberIndex, vertical);
      break;
    case 8: 
      lightSegment(leds, ledsCount, color, numberIndex, inner_line);
      lightSegment(leds, ledsCount, color, numberIndex, vertical);
      break;
    case 9: 
      lightSegment(leds, ledsCount, color, numberIndex, outer_line);
      lightSegment(leds, ledsCount, color, numberIndex, inner_line);
      lightSegment(leds, ledsCount, color, numberIndex, vertical);
      break;    
    case 0: 
      lightSegment(leds, ledsCount, color, numberIndex, outer_line);
      lightSegment(leds, ledsCount, color, numberIndex, inner_line);
      lightSegment(leds, ledsCount, color, numberIndex, primary_diagonal);
      lightSegment(leds, ledsCount, color, numberIndex, secondary_diagonal);
      lightSegment(leds, ledsCount, color, numberIndex, vertical);
      break;  
  }
}

void displayAll(CRGB leds[], byte ledsCount, CRGB colors[], byte rightTopNumber, byte leftTopNumber, byte rightBottomNumber, byte leftBottomNumber) {
  reset(leds, ledsCount);
  lightRange(leds, CRGB::White, 24, 10);
  lightNumber(leds, ledsCount, colors, rightTopNumber, 0);
  lightNumber(leds, ledsCount, colors, leftTopNumber, 1);
  lightNumber(leds, ledsCount, colors, rightBottomNumber, 2);
  lightNumber(leds, ledsCount, colors, leftBottomNumber, 3);
}
