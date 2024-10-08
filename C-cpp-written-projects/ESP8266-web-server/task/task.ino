/*
   Red and green LED connected to GPIO D0 and D1
Added:
- 5V Power Supply Module, 
- LED Matrix WS2812b 8x8 connected to D2
- 330 Ohm resistor between D2 and matrix Data-in pin
- push button to pin D6 for interrupt
 */

#include "LittleFS.h"
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B     D2
#define NUM_PIXELS      64
#define DELAY_INTERVAL  250

// const char *ssid = "*****";
// const char *password = "*****";

AsyncWebServer server(80);
Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
const uint8_t rainbow_palette[8][3] = {{238, 130, 238},{75, 0, 130},{0, 0, 255},{0, 255, 0},{255, 255, 0},{255, 127, 0},{255, 0 , 0},{1, 1, 1}};

// Interrupt Debouncing 
unsigned long button_time = 0;  
unsigned long last_button_time = 0;
volatile bool abort_sequence = false;

// timing
unsigned long one_sec_interval = 1000;
unsigned long previousMillis = 0;

// store the current output state
String redLEDState = "off";
String greenLEDState = "off";
String currentPattern = "rainbow";

// Assign output constants to GPIO pins
const uint8_t RED_LED = D0;
const uint8_t GREEN_LED = D1;
const uint8_t INTERRUPT_BUTTON = D6;

void ICACHE_RAM_ATTR isr() {
	button_time = millis();
	if (button_time - last_button_time > 250) {
		abort_sequence = true;
		last_button_time = button_time;
	}
}

void setup() {

	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, LOW);  

	Serial.begin(115200);
	pinMode(INTERRUPT_BUTTON, INPUT_PULLUP);
	attachInterrupt(INTERRUPT_BUTTON, isr, FALLING);
	if (!LittleFS.begin()) {
		Serial.println("Failed to mount file system");
		return;
	}

	// start up WiFi
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting ...");
	}
	Serial.print("Connected to ");
	Serial.print(ssid);
	Serial.print(". IP address: ");
	Serial.println(WiFi.localIP());

	// Serve the main HTML page
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
			request->send(LittleFS, "/index.html", "text/html");
			});

	// Serve the CSS file
	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
			request->send(LittleFS, "/style.css", "text/css");
			});

	// Endpoint to toggle Red LED
	server.on("/toggleRedLED", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (redLEDState == "off") {
			digitalWrite(RED_LED, HIGH);
			redLEDState = "on";
			} else {
			digitalWrite(RED_LED, LOW);
			redLEDState = "off";
			}
			request->send(200, "text/plain", redLEDState);
			});

	// Endpoint to toggle Green LED
	server.on("/toggleGreenLED", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (greenLEDState == "off") {
			digitalWrite(GREEN_LED, HIGH);
			greenLEDState = "on";
			} else {
			digitalWrite(GREEN_LED, LOW);
			greenLEDState = "off";
			}
			request->send(200, "text/plain", greenLEDState);
			});

	// Endpoint to Get Current Pattern
	server.on("/getCurrentPattern", HTTP_GET, [](AsyncWebServerRequest *request) {
			request->send(200, "text/plain", currentPattern);
			});

	server.on("/setPattern", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (request->hasParam("pattern")) {
			String pattern = request->getParam("pattern")->value();
			if (pattern == "blitz" || pattern == "rainbow_avalanche" ||
					pattern == "stacking_colors" || pattern == "stacking_rainbow" ||
					pattern == "draw_rainbow" || pattern == "slow_drift" ||
					pattern == "color_palette" || pattern == "switching_rgb" ||
					pattern == "tracer") {
			currentPattern = pattern;
			Serial.println("Pattern set to: " + currentPattern);
			request->send(200, "text/plain", "Pattern set to " + currentPattern);
			} else {
			request->send(400, "text/plain", "Invalid pattern");
			}
			} else {
			request->send(400, "text/plain", "Bad Request");
			}
			});

	server.begin();
	WS2812B.begin();
}

// int one = 1;

void loop() {
	// if (one == 1)
	//   test_one();
	// else
	//   rainbow_avalanche();
	// test_two();

	if (currentPattern == "blitz") {
		blitz();
	}
	else if (currentPattern == "rainbow_avalanche") {
		rainbow_avalanche();
	}
	// else if (currentPattern == "stacking_colors") {
	// 	stacking_colors();
	// }
	// else if (currentPattern == "stacking_rainbow") {
	// 	stacking_rainbow();
	// }
	// else if (currentPattern == "draw_rainbow") {
	// 	draw_rainbow();
	// }
	else if (currentPattern == "slow_drift") {
		slow_drift();
	}
	else if (currentPattern == "color_palette") {
		color_palette();
	}
	else if (currentPattern == "switching_rgb") {
		switching_rgb();
	}
	else if (currentPattern == "tracer") {
		tracer();
	}
	interrupt_led();
}

void  interrupt_led() {
	if (abort_sequence == true) {
		digitalWrite(RED_LED, HIGH);
		abort_sequence = false;
		delay(1000);
		digitalWrite(RED_LED, LOW);
		//     if (one == 1)
		//       one = 0;
		//     else
		//       one = 1;
	}
}
