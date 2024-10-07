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

// const char *ssid = "*****";
// const char *password = "*****";

AsyncWebServer server(80);

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

// store the current output state
String redLEDState = "off";
String greenLEDState = "off";

// Assign output variables to GPIO pins
const uint16_t RED_LED = D0;
const uint16_t GREEN_LED = D1;

const uint8_t rainbow_palette[8][3] = {{238, 130, 238},{75, 0, 130},{0, 0, 255},{0, 255, 0},{255, 255, 0},{255, 127, 0},{255, 0 , 0},{1, 1, 1}};

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
	// rainbow();
	// seq_1();
	// seq_2();
	// seq_3();
	seq_4();
}