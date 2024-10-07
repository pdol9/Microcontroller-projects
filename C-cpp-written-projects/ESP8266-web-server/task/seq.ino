// color sequences

void	avalanche() {

	WS2812B.clear();
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(1, 0, 0));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(0, 1, 0));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(0, 0, 1));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(1, 1, 1));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(1, 1, 0));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(0, 1, 1));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(1, 0, 1));
		WS2812B.show();
	}
	delay(1000);
	for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
		WS2812B.setPixelColor(pixel, WS2812B.Color(255, 255, 255));
		WS2812B.show();
	}
	delay(1000);
}

void  rainbow_avalanche() {
	WS2812B.clear();
	for (uint16_t i = 0; i < 8; ++i) {
		for (uint16_t pixel = 0; pixel < NUM_PIXELS; ++pixel) {
			WS2812B.setPixelColor(pixel, WS2812B.Color(rainbow_palette[i][0], rainbow_palette[i][1], rainbow_palette[i][2]));
			delay(20);                                                                                                    
			WS2812B.show();
		}
		delay(50);
		WS2812B.show();
	}
	delay(1000);
}

void  stacking_colors() {
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

void  stacking_rainbow() {
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

void	draw_rainbow() {
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

/*  using existing libraries  */

void slow_drift() {

	static uint16_t i = 0;
	for (int j=0; j < WS2812B.numPixels(); ++j) {
		WS2812B.setPixelColor(j, Wheel((i + j) & 255));
	}
	WS2812B.show();
	i++;
	delay(DELAY_INTERVAL);
}

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
	uint32_t colors[] = {WS2812B.Color(255, 0, 0), WS2812B.Color(0, 255, 0),
		WS2812B.Color(0, 0, 255), WS2812B.Color(255, 255, 0)};
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
