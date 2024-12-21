#include "header.h"

/*   color sequences   */

void filler() {

	WS2812B.clear();
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= DELAY_INTERVAL) {
		previousMillis = currentMillis;

		for (int j = 0; j < WS2812B.numPixels(); ++j) {
			WS2812B.setPixelColor(j, WS2812B.Color(0, j * 4, j + 64));
			if (abort_sequence == true) {
				WS2812B.clear();
				WS2812B.show();
				return;
			}
		}
		WS2812B.show();
	}
}

void blitz(const uint8_t palette[8][3]) {

	static uint8_t palette_index = 0;
	unsigned long currentMillis = millis();

	WS2812B.clear();

  // pause between color switching for 1 second
	if (currentMillis - previousMillis >= one_sec_interval) {
		previousMillis = currentMillis;

		for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
			WS2812B.setPixelColor(pixel, WS2812B.Color(palette[palette_index][0], palette[palette_index][1], palette[palette_index][2]));
			WS2812B.show();
			if (abort_sequence == true) {
				WS2812B.clear();
				WS2812B.show();
				return;
			}
		}
		++palette_index;
	palette_index &= 7;
	}
}

void rainbow_avalanche() {
	static uint8_t palette_index = 0;
	static unsigned long pixelMillis = 0;
	static unsigned long colorMillis = 0;

	unsigned long currentMillis = millis();

	if (currentMillis - colorMillis >= one_sec_interval) {
		colorMillis = currentMillis;

		if (currentMillis - pixelMillis >= 5) {
			pixelMillis = currentMillis;

			for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {

				WS2812B.setPixelColor(pixel, WS2812B.Color(rainbow_palette[palette_index][0], rainbow_palette[palette_index][1], rainbow_palette[palette_index][2]));
				if (abort_sequence == true) {
					WS2812B.clear();
					WS2812B.show();
					return;
				}
				WS2812B.show();
			}
		}

		++palette_index;
	palette_index &= 7;

		// 1-second delay before the next color switch
		colorMillis = currentMillis;
	}
}
