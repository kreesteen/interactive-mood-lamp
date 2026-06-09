# ESP32-S3 Mood Lamp

## Overview

This project is an RGB mood lamp built using an ESP32-S3 development board.

The goal of the project is not only to create a functional lamp, but also to learn the fundamentals of embedded systems development through incremental experimentation and feature additions.

The lamp currently supports PWM-based brightness control using a rotary encoder and serves as a platform for learning concepts such as GPIO, PWM, quadrature encoders, debouncing, timing control, and embedded firmware architecture.

---

## Hardware

### Microcontroller
- ESP32-S3 (Freenove ESP32-S3 WROOM)

### Components
- RGB LED module
- Rotary Encoder Module
  - Channel A
  - Channel B
  - Push Button (SW)
- Breadboard
- Jumper Wires

---

## Features Implemented

### PWM LED Brightness Control

The RGB LED brightness is controlled using PWM (Pulse Width Modulation).

Brightness values range from:

text 0   = LED Off 255 = Maximum Brightness 

The ESP32 generates the PWM signal while the LED brightness is adjusted in software.

---

### Rotary Encoder Input

A quadrature rotary encoder is used instead of a potentiometer.

The encoder provides:

- Infinite rotation
- Direction detection
- Incremental control

The firmware decodes the quadrature sequence:

text 00 → 01 → 11 → 10 → 00 

to determine rotation direction.

Clockwise rotation increases brightness.

Counter-clockwise rotation decreases brightness.

---

### Encoder Button

The encoder's built-in push button is connected using the ESP32's internal pull-up resistor:

cpp pinMode(buttonPin, INPUT_PULLUP); 

Button presses are detected using software debouncing.

---

### Software Debouncing

Mechanical switches bounce when pressed.

Without debouncing, a single button press may be interpreted as multiple presses.

The firmware uses:

- Previous button state
- Stable button state
- Debounce timer
- Debounce delay

to detect valid button events.

---

## Concepts Learned

### GPIO

Configured pins as:

cpp INPUT OUTPUT INPUT_PULLUP 

Learned the difference between floating inputs and internally pulled-up inputs.

---

### PWM

Learned:

- Duty cycle control
- Brightness control
- Mapping values between ranges
- Hardware-generated PWM on ESP32

---

### ADC

Used a rotary angle sensor (potentiometer module) to:

- Read analog values
- Convert ADC readings into voltages
- Map ADC values to PWM brightness levels

Example:

cpp brightness = adcValue * (255.0 / 4095); 

---

### Filtering

Experimented with:

- Moving average filters
- First-order low-pass filters

to reduce ADC noise.

---

### Quadrature Encoding

Learned how rotary encoders generate two square-wave outputs:

text A B 

offset by 90°.

Direction is determined by examining the state transitions.

---

### Embedded Timing

Discovered that firmware timing can significantly affect behaviour.

Observed:

- Serial printing changing system behaviour
- Polling frequency affecting responsiveness
- Input sampling rate affecting encoder performance

Experimented with:

cpp millis() 

based timing instead of relying on delays.

---

## Debugging Lessons

### Floating Inputs

Forgetting:

cpp pinMode(pin, INPUT_PULLUP); 

caused false button presses due to a floating input.

---

### Mechanical Bounce

Observed that both push buttons and rotary encoders can generate multiple transitions from a single physical action.

---

### Timing Dependence

Removing Serial output changed firmware behaviour because Serial printing unintentionally slowed the polling loop.

This demonstrated how timing can affect embedded systems.

---

## Current Status

Working:

- RGB LED output
- PWM brightness control
- Rotary encoder rotation detection
- Encoder button detection
- Software debouncing

In Progress:

- Colour mode switching
- Improved encoder filtering
- State-machine-based firmware structure

---

## Planned Features

### Mode Switching

Encoder button cycles through:

text Mode 0 - Red Brightness Mode 1 - Green Brightness Mode 2 - Blue Brightness 

---

### Full RGB Colour Mixing

Control each colour channel independently.

---

### Sound Reactive Mode

Use a sound sensor to create audio-reactive lighting effects.

---

### Display Integration

Use a 4-digit display module to show:

- Brightness
- Current Mode
- RGB Values

---

### Future Improvements

- Interrupt-driven encoder handling
- RTOS tasks
- Non-blocking scheduler architecture
- Preset colour profiles
- Smooth colour transitions
- Persistent settings storage

---

## Project Goal

This project serves as a practical introduction to embedded systems engineering.

The focus is on learning:

- Hardware interfacing
- Firmware design
- Debugging techniques
- Real-time system concepts

while gradually building a complete interactive RGB mood lamp.
