# Embedded systems projects

## Description

Below is a group of several projects based on Arduino board and ESP8266.

There are two directories, containing C/C++ and Rust codebase respectively.

### Blinking LEDs

Build a circuit with a red, yellow and green LEDs. Red and yellow should blink
interchangeably. With a press to a switch, green should turn on and the previous
LEDs will turn off.

Second part does similar, but this time red and yellow LEDs blink interchangeably.

Third part includes red LED additional blinking.

### LCD screen - voltage regulator

First part of the project consists of a LCD screen and potentiometer. With the
help of the latter, LCD should display voltage value which is being regulated
via potentiometer.

Second part makes possible to enter voltage value via serial connection (console)
instead of using potentiometer.

### Light-tracking device

Goal of this project is to make a light-tracking device. Device will detect the
(brightest) light source and rotate towards it. It uses two servos and three
photoresistors so it can rotate and scan in all directions.

### Remote control of LED-matrix via webserver/ESP8266 

A webpage being hosted on ESP8266 which enables to run via browser several color sequences on
LED Matrix WS2812B-64.


### TODO

ESP8266 webserver:
- add interrupt function / button, with red-green LED indication
- add button to change webpage light/dark theme (e.g. background)
- optimise code and polish color sequences
