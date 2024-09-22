#include <ESP8266WiFi.h>

// network credentials
const char *ssid = "replace";
const char *password = "replace";

// web server port
WiFiServer server(80);

// store the HTTP request
String header;

// store the current output state
String RED_LEDState = "off";
String GREEN_LEDState = "off";

// Assign output variables to GPIO pins
const int RED_LED = D0;
const int GREEN_LED = D1;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {

  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // Connect to Wi-Fi network and run server
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.accept();        // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();
        Serial.write(c);
        header += c;
       
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /D0/on") >= 0) {
              Serial.println("GPIO D0 (red LED) on");
              RED_LEDState = "on";
              digitalWrite(RED_LED, HIGH);
            } else if (header.indexOf("GET /D0/off") >= 0) {
              Serial.println("GPIO D0 (red LED) off");
              RED_LEDState = "off";
              digitalWrite(RED_LED, LOW);
            } else if (header.indexOf("GET /D1/on") >= 0) {
              Serial.println("GPIO D1 (green LED) on");
              GREEN_LEDState = "on";
              digitalWrite(GREEN_LED, HIGH);
            } else if (header.indexOf("GET /D1/off") >= 0) {
              Serial.println("GPIO D1 (green LED) off");
              GREEN_LEDState = "off";
              digitalWrite(GREEN_LED, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
           
            client.println(".container { display: flex; justify-content: center; gap: 20px; } .column { flex: 1; max-width: 200px; }");
            client.println(".button, .button2 { width: 200px; background-color: #4CAF50; border: none; color: white; padding: 16px; text-decoration: none; font-size: 30px; margin: 5px 2px; display: inline-block; }");
            client.println(".button2 { background-color: gray; }");
            client.println(".button3 { background-color: #c4d4e3; border: 2px solid black; padding: 16px 40px; text-decoration: none; font-size: 30px; color: black; margin: 5px 2px; cursor: pointer; transform: scale(0.5); transform-origin: center; }");
            client.println(".red-border { width: 100px; color: red; border: 3px solid red; padding: 5px; display: inline-block; }");
            client.println(".green-border { width: 100px; color: green; border: 3px solid green; padding: 5px; display: inline-block; } </style> </head> <body>");
            client.println("<h1>ESP8622 Web Server</h1>");
          
            client.println("<div class=\"container\"> <div class=\"column\"><p class=\"red-border\">gpio D0</p>");
            if (RED_LEDState=="off") {
              client.println("<p><button class=""button2"">Status: OFF</button></p>" \
              "<p><a href=\"/D0/on\"><button class=\"button3\">ON</button></a></p></div>");
            } else {
              client.println("<p><button class=""button"">Status: ON</button></p>" \
              "<p><a href=\"/D0/off\"><button class=\"button3\">OFF</button></a></p></div>");
            } 
               
            client.println("<div class=\"column\"> <p class=\"green-border\">gpio D1</p>");
            if (GREEN_LEDState=="off") {
              client.println("<p><button class=""button2"">Status: OFF</button></p>" \
              "<p><a href=\"/D1/on\"><button class=\"button3\">ON</button></a></p></div>");
            } else {
              client.println("<p><button class=""button"">Status: ON</button></p>" \
              "<p><a href=\"/D1/off\"><button class=\"button3\">OFF</button></a></p></div>");
            }
            client.println("</div></body></html>");
            
            client.println();       // The HTTP response ends with another blank line
            break;
          } else {                  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
