#include "display.h"

#define SEGMENTS_COUNT 5
#define LEDS_IN_SEGMENT 4
#define POSITIONS 4

#define NOT_USED_LED 255

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
byte led_map[POSITIONS][SEGMENTS_COUNT][LEDS_IN_SEGMENT] = {
  // top right, first position
  { 
    /* outer_line         */ {45, 41, NOT_USED_LED, NOT_USED_LED},
    /* inner_line         */ {42, 38, NOT_USED_LED, NOT_USED_LED},
    /* primary_diagonal   */ {44, 39, NOT_USED_LED, NOT_USED_LED},
    /* secondary_diagonal */ {43, 40, NOT_USED_LED, NOT_USED_LED},
    /* vertical           */ {34, 35, 36, 37},
  },
  // top left, second position
  { 
    /* outer_line         */ {53, 49, NOT_USED_LED, NOT_USED_LED},
    /* inner_line         */ {50, 46, NOT_USED_LED, NOT_USED_LED},
    /* primary_diagonal   */ {48, 51, NOT_USED_LED, NOT_USED_LED},
    /* secondary_diagonal */ {52, 47, NOT_USED_LED, NOT_USED_LED},
    /* vertical           */ {54, 55, 56, 57},
  },
  // bottom right, third position
  { 
    /* outer_line         */ {8, 4, NOT_USED_LED, NOT_USED_LED},
    /* inner_line         */ {11, 7, NOT_USED_LED, NOT_USED_LED},
    /* primary_diagonal   */ {9, 6, NOT_USED_LED, NOT_USED_LED},
    /* secondary_diagonal */ {10, 5, NOT_USED_LED, NOT_USED_LED},
    /* vertical           */ {0, 1, 2, 3},
  },
  // bottom left, fourth position
  { 
    /* outer_line         */ {16, 12, NOT_USED_LED, NOT_USED_LED},
    /* inner_line         */ {19, 15, NOT_USED_LED, NOT_USED_LED},
    /* primary_diagonal   */ {13, 18, NOT_USED_LED, NOT_USED_LED},
    /* secondary_diagonal */ {17, 14, NOT_USED_LED, NOT_USED_LED},
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

void lightSegment(CRGB leds[], CRGB color, byte numberIndex, Segment segment) {
  for(int i = 0; i < LEDS_IN_SEGMENT; i++) {
    int idx = led_map[numberIndex][segment][i];
    if (idx != NOT_USED_LED) 
      leds[idx] = color;
  }
}

void lightNumber(CRGB leds[], CRGB colors[], byte number, byte numberIndex) {
  int num = number % 10;
  CRGB color = colors[number / 10];
  switch (num) {
    case 1: 
      lightSegment(leds, color, numberIndex, outer_line);
      break;
    case 2: 
      lightSegment(leds, color, numberIndex, inner_line);
      break;
    case 3: 
      lightSegment(leds, color, numberIndex, primary_diagonal);
      break;
    case 4: 
      lightSegment(leds, color, numberIndex, secondary_diagonal);
      break;    
    case 5: 
      lightSegment(leds, color, numberIndex, outer_line);
      lightSegment(leds, color, numberIndex, secondary_diagonal);
      break;
    case 6: 
      lightSegment(leds, color, numberIndex, vertical);
      break;
    case 7: 
      lightSegment(leds, color, numberIndex, outer_line);
      lightSegment(leds, color, numberIndex, vertical);
      break;
    case 8: 
      lightSegment(leds, color, numberIndex, inner_line);
      lightSegment(leds, color, numberIndex, vertical);
      break;
    case 9: 
      lightSegment(leds, color, numberIndex, outer_line);
      lightSegment(leds, color, numberIndex, inner_line);
      lightSegment(leds, color, numberIndex, vertical);
      break;    
    case 0: 
      lightSegment(leds, color, numberIndex, outer_line);
      lightSegment(leds, color, numberIndex, inner_line);
      lightSegment(leds, color, numberIndex, primary_diagonal);
      lightSegment(leds, color, numberIndex, secondary_diagonal);
      lightSegment(leds, color, numberIndex, vertical);
      break;  
  }
}

void displayAll(CRGB leds[], CRGB colors[], byte rightTopNumber, byte leftTopNumber, byte rightBottomNumber, byte leftBottomNumber) {
  lightRange(leds, CRGB::White, 24, 10);
  lightNumber(leds, colors, rightTopNumber, 0);
  lightNumber(leds, colors, leftTopNumber, 1);
  lightNumber(leds, colors, rightBottomNumber, 2);
  lightNumber(leds, colors, leftBottomNumber, 3);
}
