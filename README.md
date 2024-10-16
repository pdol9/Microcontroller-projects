# Embedded systems projects

## Description

Below is a group of several projects based on Arduino Uno R3 and ESP8266.
It's a beginner's entry point to embedded systems and programming microcontrollers.

There are two directories, containing C/C++ and Rust codebase respectively.
C/C++ code is WIP, while projects rewritten into Rust will follow thereafter.

## Listed projects

- blinking LEDs
- LCD screen
- light-tracking device
- webserver for color sequences on led matrix

### Blinking LEDs

This project has a sequence of a red, yellow and green LEDs blinking. Red and
yellow should blink interchangeably. With a press to a switch, green should turn
on and the previous LEDs will turn off.

A second variation does similar, but this time red and yellow LEDs blink
interchangeably.

Third variation includes red LED additional blinking.

### LCD screen - voltage regulator

Part of the project consists of a LCD screen and potentiometer. With the
help of the latter, LCD should display voltage value which is being regulated
via potentiometer.

Next part makes possible to enter voltage value via serial connection (console)
instead of using potentiometer.

### Light-tracking device

Goal of this project is to make a light-tracking device. Device will detect the
(brightest) light source and rotate towards it. It uses two servos and three
photoresistors so it can rotate and scan in all directions.

### TODO

- restructure project base with independent README files and project expensions
