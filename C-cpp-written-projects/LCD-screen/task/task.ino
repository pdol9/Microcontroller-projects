#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LED 9
#define TEXT_PIN 7

void setup() {

    Serial.begin(9600);
    lcd.begin(16, 2);
    analogWrite(TEXT_PIN, 0);
    pinMode(LED, OUTPUT);
}

void loop() {

    int sensorValue = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);

    // analogWrite(LED, (sensorValue/4));
    // lcd.setCursor(0,0);
    // lcd.print(voltage);
    // Serial.println(voltage);
    // delay(200);


    // BONUS
    Serial.println("Enter the value for brightness between 0 and 255");
    while (Serial.available() == 0)
        continue;
    unsigned char voltage_int = Serial.readString().toInt()%256;
    Serial.println(voltage_int);
    lcd.clear();
    float voltage_converted = float(voltage_int)/ 255 * 5;
    lcd.print(voltage_converted);
    analogWrite(LED, voltage_int);
}

