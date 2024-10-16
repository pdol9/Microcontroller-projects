# Remote control of LED Matrix via webserver/ESP8266 

This project is a hosted webpage on ESP8266 which enables to run via
browser several color sequences on LED Matrix WS2812B-64.

## Hardware setup

- breadboard
- red and green LED connected to GPIO D0 and D1
- 5V Power Supply Module connectecd to same (power and ground) buses
	as LED Matrix, its ground rail is connected to ESP ground pin
- LED Matrix WS2812b 8x8 module data pin connected to pin D2
- 330 Ohm resistor between D2 and Matrix module Data-in pin
- push (interrupt) button connected to pin D6 for color sequence interruption

## Software setup

At the moment code is only possible to compile and upload with Arduino IDE.
Webserver is written in a non-blocking behaviour using ESPAsyncWebServer library.
The color sequences are following the suit which makes possible to interrupt them
during their execution, by using a physical (push) button or web interface.

During sequence interrupt a green led will turn off and red will turn on for a
brief moment (1,5 s).

## Color sequences


## TODO
```
- polish color sequences
- list color sequences in README.md
```
