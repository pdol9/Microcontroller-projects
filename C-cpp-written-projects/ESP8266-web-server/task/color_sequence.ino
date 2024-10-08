/*   color sequences   */

// pause between color switching for 1 second
void blitz() {

	const static uint8_t palette[8][3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 1, 1 }, { 1, 1, 0 }, { 0, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };
	static uint8_t palette_index = 0;
	unsigned long currentMillis = millis();

	WS2812B.clear();

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
		if (palette_index > 7)
			palette_index = 0;
	}
}

void a_rainbow_avalanche() {
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

		palette_index++;
		if (palette_index > 7) {
			palette_index = 0;
		}

		// 1-second delay before the next color switch
		colorMillis = currentMillis;
	}
}

// TODO non-blocking behaviour
void pallete() {
	WS2812B.clear();

	for (uint16_t i = 0; i < 8; ++i) {
		for (uint16_t stacked = 0; stacked < NUM_PIXELS; ++stacked) {
			for (uint16_t pixel = 0; pixel < NUM_PIXELS - stacked; ++pixel) {
				WS2812B.setPixelColor(pixel, WS2812B.Color(rainbow_palette[i][0], rainbow_palette[i][1], rainbow_palette[i][2]));
				WS2812B.setPixelColor(pixel - 1, WS2812B.Color(0, 0, 0));
				WS2812B.show();
				delay(50);
			}
			delay(80);
			WS2812B.show();
		}
		delay(1000);
	}
}

// TODO non-blocking behaviour
void rainbow() {
	WS2812B.clear();
	for (uint16_t stacked = 0; stacked < NUM_PIXELS; ++stacked) {
		for (uint16_t i = 0; i < 8; ++i, ++stacked) {
			for (uint16_t pixel = 0; pixel < NUM_PIXELS - stacked; ++pixel) {
				WS2812B.setPixelColor(pixel, WS2812B.Color(rainbow_palette[i][0], rainbow_palette[i][1], rainbow_palette[i][2]));
				WS2812B.setPixelColor(pixel - 1, WS2812B.Color(0, 0, 0));
				WS2812B.show();
				delay(50);
			}
			delay(80);
			WS2812B.show();
		}
		--stacked;
		delay(1000);
	}
}

// TODO non-blocking behaviour
void get_rainbow() {
	WS2812B.clear();
	for (uint16_t pixel = 0; pixel < 8; ++pixel) {
		for (uint16_t i = 0; i < 8; ++i) {
			WS2812B.setPixelColor(pixel + i * 8, WS2812B.Color(rainbow_palette[i][0], rainbow_palette[i][1], rainbow_palette[i][2]));
			WS2812B.show();
		}
		delay(100);
	}
	delay(2000);
}

void drift() {

	WS2812B.clear();
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= DELAY_INTERVAL) {
		previousMillis = currentMillis;

		static uint16_t i = 0;
		for (int j = 0; j < WS2812B.numPixels(); ++j) {
			WS2812B.setPixelColor(j, Wheel((i + j) & 255));
			if (abort_sequence == true) {
				WS2812B.clear();
				WS2812B.show();
				return;
			}
		}
		WS2812B.show();
		i++;
	}
}

void test_one() {

	WS2812B.clear();
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= DELAY_INTERVAL) {
		previousMillis = currentMillis;

		static uint16_t i = 0;
		for (int j = 0; j < WS2812B.numPixels(); ++j) {
			int k = j / 4;
			WS2812B.setPixelColor(j, WS2812B.Color(i, k, k));
			if (abort_sequence == true) {
				WS2812B.clear();
				WS2812B.show();
				return;
			}
		}
		WS2812B.show();
		i++;
	}
}

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

/*  using existing libraries  */

void color_palette() {

	static uint16_t i = 0;
	WS2812B.clear();
	for (int j = 0; j < WS2812B.numPixels(); ++j) {
		WS2812B.setPixelColor(j, Wheel((i + j * 10) & 255));
	}
	WS2812B.show();
	i++;
	delay(DELAY_INTERVAL);
}

void switching_rgb() {

	static uint8_t colorIndex = 0;
	uint32_t colors[] = { WS2812B.Color(255, 0, 0), WS2812B.Color(0, 255, 0),
		WS2812B.Color(0, 0, 255), WS2812B.Color(255, 255, 0) };
	WS2812B.clear();
	for (int j = 0; j < WS2812B.numPixels(); ++j) {
		WS2812B.setPixelColor(j, colors[colorIndex]);
	}
	WS2812B.show();
	colorIndex = (colorIndex + 1) % 4;
	delay(DELAY_INTERVAL * 10);
}

void tracer() {

	static int pos = 0;
	WS2812B.clear();
	WS2812B.setPixelColor(pos, WS2812B.Color(255, 255, 255));
	WS2812B.show();
	pos = (pos + 1) % WS2812B.numPixels();
	delay(DELAY_INTERVAL);
}

// Helper function to generate rainbow colors
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return WS2812B.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return WS2812B.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return WS2812B.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
