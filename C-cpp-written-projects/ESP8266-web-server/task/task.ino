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

// store the current sequence
String currentPattern = "Default";

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
	digitalWrite(GREEN_LED, HIGH);  

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

	// Endpoint to stop the current LED sequence
	server.on("/abort_sequence", HTTP_GET, [](AsyncWebServerRequest *request) {
			abort_sequence = true;
			request->send(200, "text/plain", "Sequence Stopped");
			});

	// Endpoint to toggle background between light and dark mode
	server.on("/toggle_background", HTTP_GET, [](AsyncWebServerRequest *request) {
			static bool darkMode = false;
			darkMode = !darkMode;
			String mode = darkMode ? "dark" : "light";
			request->send(200, "text/plain", mode);
			});

	// Endpoint to Get Current Pattern
	server.on("/getCurrentPattern", HTTP_GET, [](AsyncWebServerRequest *request) {
			request->send(200, "text/plain", currentPattern);
			});

	server.on("/setPattern", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (request->hasParam("pattern")) {
			String pattern = request->getParam("pattern")->value();
			if (pattern == "blitz" || pattern == "a_rainbow_avalanche" ||
					pattern == "pelette" || pattern == "rainbow" ||
					pattern == "get_rainbow" || pattern == "drift" ||
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


void loop() {
	switch (currentPattern[0]) {
		case 'b': blitz(); break;
		case 'a': a_rainbow_avalanche(); break;
		case 'p': pallete(); break;
		case 'r': rainbow(); break;
		case 'g': get_rainbow(); break;
		case 'd': drift(); break;
		case 'c': color_palette(); break;
		case 's': switching_rgb(); break;
		case 't': tracer(); break;
		default: filler(); break;
	}
	interrupt_led();
}

void  interrupt_led() {
	if (abort_sequence == true) {
		digitalWrite(GREEN_LED, LOW);
		digitalWrite(RED_LED, HIGH);
		abort_sequence = false;
		currentPattern = "Default";
		delay(1500);
		digitalWrite(RED_LED, LOW);
		digitalWrite(GREEN_LED, HIGH);
	}
}