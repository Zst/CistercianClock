#ifndef CONFIG_H
#define CONFIG_H

#define NUM_LEDS 58
#define BRIGHTNESS 100
#define DATA_PIN 23

#define NTP_SERVER "time3.google.com"
#define DEFAULT_TIMEZONE "Europe/Amsterdam"
#define DEFAULT_APN_NAME "CistercianClock"
#define DEFAULT_APN_PASSWORD "ledclock"

#define NUM_COLORS 6
CRGB led_colors[NUM_COLORS] = {
  0xF60000,
  0xFF8C00,
  0xFFEE00,
  0x4DE94C,
  0x3783FF,
  0x4815AA
};
//CRGB led_colors[NUM_COLORS] = {
//  0xfc2847,
//  0xffa343,
//  0xfdfc74,
//  0x71bc78,
//  0x0f4c81,
//  0x7442c8
//};

#define IDLE_MIN_LED 24
#define IDLE_MAX_LED 33
#define IDLE_DELAY 50

#endif
