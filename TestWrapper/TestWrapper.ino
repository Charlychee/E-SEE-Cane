// Author: Charles Lee ccl002@ucsd.edu
#include "TFLWrapper.h"
#include <Wire.h>

#define TFL_TOP_ADDRESS 0x10
#define TFL_BOT_ADDRESS 0x20

// red - pinky
// grey - index
// yellow - ring
// orange - middle
#define BUZZ1 4
#define BUZZ2 5
#define BUZZ3 6
#define BUZZ4 7

#define NEAR 50
#define FAR 100

TFLWrapper theTopTFL(TFL_TOP_ADDRESS);
TFLWrapper theBotTFL(TFL_BOT_ADDRESS);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize buzz motors
  pinMode(BUZZ1, OUTPUT);
  pinMode(BUZZ2, OUTPUT);
  pinMode(BUZZ3, OUTPUT);
  pinMode(BUZZ4, OUTPUT);
}

void loop() {
  theTopTFL.checkData();
  theBotTFL.checkData();

  digitalWrite(BUZZ1, theBotTFL.getDist() < NEAR ? HIGH : LOW);
  digitalWrite(BUZZ2, theBotTFL.getDist() < FAR ? HIGH : LOW);
  digitalWrite(BUZZ3, theTopTFL.getDist() < NEAR ? HIGH : LOW);
  digitalWrite(BUZZ4, theTopTFL.getDist() < FAR ? HIGH : LOW);
}