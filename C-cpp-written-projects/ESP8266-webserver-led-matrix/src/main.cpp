#include "header.h"

// const char *ssid = "*****";
// const char *password = "*****";

AsyncWebServer server(80);
Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
const uint8_t rainbow_palette[8][3] = {{238, 130, 238},{75, 0, 130},{0, 0, 255},{0, 255, 0},{255, 255, 0},{255, 127, 0},{255, 0, 0},{1, 1, 1}};

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

void IRAM_ATTR isr() {
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
    Serial.println("Failed to mount file system.");
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
      if (pattern == "a-blitz" || pattern == "b-rainbow_avalanche" ||
          pattern == "c-tracer") {
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

  const static uint8_t palette[8][3] = {{1,0,0}, {0,1,0}, {0,0,1}, {1,1,1}, {1,1,0}, {0,1,1}, {1,0,1}, {1,1,1}};

  switch (currentPattern[0]) {
    case 'a': blitz(palette); break;
    case 'b': rainbow_avalanche(); break;
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
    delay(1200);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
}
