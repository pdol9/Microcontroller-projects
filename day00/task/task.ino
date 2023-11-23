const int buttonPin = 2;                // the number of the pushbutton pin
const int LEDGreen = 13;                // the number of the LED pin
const int LEDYellow = 12;
const int LEDRed = 11;
const int UP = 1;
const int DOWN = 0;

int switching = 0;

void setup() {
    // initialize the LED pin as an output:
    pinMode(LEDGreen, OUTPUT);
    pinMode(LEDYellow, OUTPUT);
    pinMode(LEDRed, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT_PULLUP);
}

void  turn_green() {
    digitalWrite(LEDGreen, HIGH);
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDYellow, LOW);
    while (digitalRead(buttonPin) == UP)
        continue;
    switching = 1;
}

void  turn_red_yellow() {

    digitalWrite(LEDGreen, LOW);
    while (1) {

        digitalWrite(LEDYellow, HIGH);
        digitalWrite(LEDRed, HIGH);
        delay(50);
        digitalWrite(LEDYellow, LOW);
        digitalWrite(LEDRed, LOW);
        for (int i = 0; i < 19; ++i) {
            if (digitalRead(buttonPin) == DOWN) {
                switching = 0;
                return;
            }
            delay(50);
        }
    }
}

void loop() {

    if (switching == 0)
        turn_green();
    else if (switching == 1)
        turn_red_yellow();

    while(digitalRead(buttonPin) == DOWN)
        delay(50);
}

