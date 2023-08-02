#include <Wire.h>               // sensor communication
#include "Adafruit_TCS34725.h"  // RGB sensor library


#define RGB_BLUE 11

//#define LEDS {2,3,4,5,6,7,8,9}

#define commonAnode true

// byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
void setup() {
  // Serial monitor setup
  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    //while (1)
      ;
  }

  //pinMode(RGB_RED, OUTPUT);
  //pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
  
  //for (int i = 0; i < sizeof(LEDS); i++)
  //  pinMode(LEDS[i], OUTPUT)

}


void loop() {
  float red, green, blue;

  analogWrite(RGB_BLUE, 255);

  tcs.setInterrupt(true);

  delay(60);

  tcs.getRGB(&red, &green, &blue);

  // tcs.setInterrupt(true);
  
  Serial.print("R:\t");
  Serial.print(int(red));
  Serial.print("\tG:\t");
  Serial.print(int(green));
  Serial.print("\tB:\t");
  Serial.print(int(blue));
  Serial.print("\n");
  

  int num_led = floor(green / 255 * 9);

  for (int i = 2; i < 2 + num_led; i++) {
    analogWrite(i, 255);
  }
  for (int i = 2 + num_led; i <= 9; i++) {
    analogWrite(i, 0);
  }
}

