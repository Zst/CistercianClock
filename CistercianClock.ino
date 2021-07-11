#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <FastLED.h> // https://github.com/FastLED/FastLED
#include <ezTime.h> // https://github.com/ropg/ezTime
#include <WiFi.h>

#include "config.h"
#include "display.h"

CRGB leds[NUM_LEDS];
WiFiManager wm;
Timezone timezone;
bool isConnected = false;

CRGB idleColor = led_colors[random(NUM_COLORS)];
byte idleIdx = IDLE_MIN_LED;
bool idleGoingUp = true;

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  
  FastLED.setBrightness(BRIGHTNESS);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  wm.setConnectRetries(4);
  wm.setConfigPortalBlocking(false);
  setServer(NTP_SERVER);
  isConnected = wm.autoConnect(DEFAULT_APN_NAME, DEFAULT_APN_PASSWORD);
  if (!isConnected) {
    Serial.println("failed to connect");
  } else { 
    Serial.println("connected");
    timezone.setLocation(DEFAULT_TIMEZONE);
  }
}

void loop() {
  wm.process();
  events();
  if (isConnected && timeStatus() == timeSet) {
    displayAll(leds, NUM_LEDS, led_colors, timezone.second(), timezone.minute(), timezone.hour(), timezone.day());
    FastLED.delay(1000);
  } else {
    reset(leds, NUM_LEDS);
    idleIdx += idleGoingUp ? 1 : -1;
    if (idleIdx > IDLE_MAX_LED) {
      idleGoingUp = false;
      idleIdx = IDLE_MAX_LED;
    }
    if (idleIdx < IDLE_MIN_LED) {
      idleGoingUp = true;
      idleIdx = IDLE_MIN_LED;
      idleColor = led_colors[random(NUM_COLORS)];
    }
    leds[idleIdx] = idleColor;
    FastLED.delay(IDLE_DELAY);
  }
}
