#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>

#include "LittleFS.h"
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B		D2
#define NUM_PIXELS		64
#define DELAY_INTERVAL	250

// function signature
void 		interrupt_led();
void		blitz(const uint8_t palette[8][3]);
void		rainbow_avalanche();
void		filler();
uint32_t	Wheel(byte WheelPos);


// main structs
extern AsyncWebServer server;
extern Adafruit_NeoPixel WS2812B;
extern const uint8_t rainbow_palette[8][3];

// Interrupt Debouncing 
extern unsigned long button_time;
extern unsigned long last_button_time;
extern volatile bool abort_sequence;

// timing
extern unsigned long one_sec_interval;
extern unsigned long previousMillis;

#endif
