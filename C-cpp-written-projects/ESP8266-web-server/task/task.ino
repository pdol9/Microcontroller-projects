/*
  Red and green LED connected to GPIO D0 and D1
  Added:
  - 5V Power Supply Module, 
  - LED Matrix WS2812b 8x8 connected to D2
  - 330 Ohm resistor between D2 and matrix Data-in pin
*/

#include "LittleFS.h"
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B  D2
#define NUM_PIXELS   64
#define DELAY_INTERVAL 250

const char *ssid = "*****";
const char *password = "*****";

AsyncWebServer server(80);

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

// store the current output state
String redLEDState = "off";
String greenLEDState = "off";

// Assign output variables to GPIO pins
const int RED_LED = D0;
const int GREEN_LED = D1;

void setup() {

	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, LOW);  

	Serial.begin(115200);
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
  server.begin();
  WS2812B.begin();
}

void loop() {

  WS2812B.clear();

  // turn pixels to green one by one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; ++pixel) {
    WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));
    WS2812B.show();
    delay(DELAY_INTERVAL);
  }
  delay(1000);
  // turn on all pixels to pink at the same time
  for (int pixel = 0; pixel < NUM_PIXELS; ++pixel) {
    WS2812B.setPixelColor(pixel, WS2812B.Color(255, 0, 255));
  }
  WS2812B.show();
  delay(1000);
  // count down by turning pixels to blue
  for (int pixel = NUM_PIXELS - 1; pixel >= 0; --pixel) {
    WS2812B.setPixelColor(pixel, WS2812B.Color(0, 0, 255));
    WS2812B.show();
    delay(DELAY_INTERVAL);
  }
  delay(2000);
}