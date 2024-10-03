#include "LittleFS.h"
#include <ESPAsyncWebServer.h>

const char *ssid = "*****";
const char *password = "*****";

AsyncWebServer server(80);

// store the current output state
String redLEDState = "off";
String greenLEDState = "off";

// Assign output variables to GPIO pins
const int RED_LED = D0;
const int GREEN_LED = D1;

String processor(const String& var) {

	if (var == "redLEDState") {
		return redLEDState;
	} else if (var == "greenLEDState") {
		return greenLEDState;
	}
	return String();
}

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

	// Route the main HTML page
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", String(), false, processor);
    });
	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css", "text/css");
    });

	// Route to toggle red LED
	server.on("/toggleRedLED", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (redLEDState == "off") {
      digitalWrite(RED_LED, HIGH);
      redLEDState = "on";
    } else {
      digitalWrite(RED_LED, LOW);
      redLEDState = "off";
    }
    request->send(200, "text/plain", redLEDState); // Return new state
    });

	// Route to toggle green LED
	server.on("/toggleGreenLED", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (greenLEDState == "off") {
        digitalWrite(GREEN_LED, HIGH);
        greenLEDState = "on";
			} else {
        digitalWrite(GREEN_LED, LOW);
        greenLEDState = "off";
			}
			request->send(200, "text/plain", greenLEDState); // Return new state
			});

	// Endpoint to get red LED status
	server.on("/redLedStatus", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", redLEDState);
    });

	// Endpoint to get green LED status
	server.on("/greenLedStatus", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", greenLEDState);
    });

	server.begin();
}

void loop() {}