# Remote control of LED Matrix via webserver/ESP8266 

## Description

This project hosts a webpage on ESP8266 which can run several color sequences
on LED Matrix WS2812B-64.

Webserver is written in a non-blocking behaviour using ESPAsyncWebServer library.
The color sequences are programmed in a way which makes possible to interrupt them
during their execution, either by using a physical (push) button or web interface.

During sequence interrupt a green led will turn off and red will turn on for a
brief moment (1,5 s).

## Hardware setup

- breadboard
- red and green LED connected to GPIO D0 and D1
- 5V Power Supply Module connectecd to same (power and ground) buses
	as LED Matrix, its ground rail is connected to ESP ground pin
- LED Matrix WS2812b 8x8 module data pin connected to pin D2
- 330 Ohm resistor between D2 and Matrix module Data-in pin
- push (interrupt) button connected to pin D6 for color sequence interruption

##  Installation

At the moment code is only possible to compile and upload with Arduino IDE.

There are several steps to do to access the website:
- Upload files in ```data``` directory using LittleFS library.
- Replace value of ```*ssid``` with a valid name of the WiFi and same with
value of ```*password```.
- Upload the code to the ESP8266.
- Open Serial monitor in Arduino IDE and enter local IP address given in the
Serial monitor into the browser.

### Color sequences (Description)
```WIP```

### TODO
```
- polish color sequences
- list color sequences in README.md
```
