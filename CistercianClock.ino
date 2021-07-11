#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <FastLED.h>

#include "display.h"

#define NUM_LEDS 58
#define DATA_PIN 23
CRGB leds[NUM_LEDS];
WiFiManager wm;


void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  
  FastLED.setBrightness(100);
  WiFi.mode(WIFI_AP); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  wm.setConnectRetries(4);
  wm.setConfigPortalBlocking(false);
  bool res = wm.autoConnect("CistercianClock", "led");
  if(!res) {
      Serial.println("Failed to connect");
  } else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected...yeey :)");
  }

}



void loop() {
  wm.process();

  for (int i = 0; i < 59; i++) {
      displayAll(leds, NUM_LEDS, i, i, i, i);
      FastLED.show();
      delay(1000);
  }
}
