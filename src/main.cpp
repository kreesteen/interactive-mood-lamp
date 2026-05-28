#include <Arduino.h>

const int RED_PIN = 45;
const int GREEN_PIN = 48;
const int BLUE_PIN = 47;

const int OUTPUT_A = 40;
const int OUTPUT_B = 41;

int brightness = 0;

int lastEncoderValue = 0;

void setColour(int red, int green, int blue);
int rotaryEncoder();

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(OUTPUT_A, INPUT_PULLUP);
  pinMode(OUTPUT_B, INPUT_PULLUP);
}

void loop() {
  // for (int i = 0; i < 255; i += 10) {
  //   analogWrite(RED_PIN, i);
  //   delay(30);
  // }

  // for (int j = 255; j > 0; j -= 10) {
  //   analogWrite(RED_PIN, j);
  //   delay(30);
  // }

  int encoderDelta = rotaryEncoder();
  brightness += encoderDelta * 10;
  if (brightness < 0) {
    brightness = 0;
  }
  else if (brightness > 255) {
    brightness = 255;
  }


  analogWrite(RED_PIN, brightness);
  Serial.println(brightness);
  // if (encoderDelta != lastEncoderValue) {
  //   Serial.println(encoderDelta);
  //   lastEncoderValue = encoderDelta;
  // }

}

void setColour(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}


int lastState = 0;
int lastDisplayed = -999;

int rotaryEncoder() {
  int a = digitalRead(OUTPUT_A);
  int b = digitalRead(OUTPUT_B);

  int val = 0; 

  int state = (a << 1) | b;

  if (state != lastState) {

    if ((lastState == 0b00 && state == 0b01) ||
        (lastState == 0b01 && state == 0b11) ||
        (lastState == 0b11 && state == 0b10) ||
        (lastState == 0b10 && state == 0b00)) {

      val = 1;
    }
    else if ((lastState == 0b00 && state == 0b10) ||
             (lastState == 0b10 && state == 0b11) ||
             (lastState == 0b11 && state == 0b01) ||
             (lastState == 0b01 && state == 0b00)) {

      val = -1;
    }

    lastState = state;
  }

  return val;

}