// color sequences

// avalanche
void	seq_1() {

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

// rainbow avalanche
void  seq_2() {
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

// stacking color
void  seq_3() {
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

// stacking rainbow
void  seq_4() {
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

void	rainbow() {
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