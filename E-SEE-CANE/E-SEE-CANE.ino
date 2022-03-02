// Author: Charles Lee - ccl002@ucsd.edu

#include "TFLWrapper.h"
#include <Wire.h>
#include "Timer.h"
#include "DiffBuffer.h"

#define TFL_TOP_ADDRESS 0x10
#define TFL_BOT_ADDRESS 0x20

// pointer - yellow
// middle - red
// ring - gray
// orange - pinky
#define POINTER 4
#define MIDDLE 5
#define RING 6
#define PINKY 7

// Distance in 
#define NEAR 50
#define FAR 100

#define CLIFF_THRESH 50
#define BUZZER_PIN 9

TFLWrapper theTopTFL(TFL_TOP_ADDRESS);
TFLWrapper theBotTFL(TFL_BOT_ADDRESS);

DiffBuffer<50> TopBuffer(CLIFF_THRESH);
DiffBuffer<50> BotBuffer(CLIFF_THRESH);

bool buzzSpeaker = false;

void processData() {
  // Retrieves data from sensors and push information to hardware
  theTopTFL.checkData();
  theBotTFL.checkData();
  Serial.print("TOP: ");
  Serial.print(theTopTFL.getDist());
  Serial.print(", BOT: ");
  Serial.println(theBotTFL.getDist());

  buzzMotor(theTopTFL.getDist(), theBotTFL.getDist());
  checkCliff();
}

void speakerTone() {
  // Buzzes the speaker tone if cliff detected, stops if not detected
  if (buzzSpeaker) {
    Serial.println("Buzzing!");
    tone(BUZZER_PIN, 1000);
    buzzSpeaker = false;
  }
  else {
    Serial.println("Stopping Buzz");
    noTone(BUZZER_PIN);
  }
}

Timer processDataTimer(100, &processData);
Timer speakerToneTimer(2000, &speakerTone);

void buzzMotor(int16_t topDist, int16_t botDist) {
  // Buzzes the motors based on the distance seen by sensors
  digitalWrite(POINTER, botDist < NEAR ? HIGH : LOW);
  digitalWrite(MIDDLE, botDist < FAR ? HIGH : LOW);
  digitalWrite(RING, topDist < NEAR ? HIGH : LOW);
  digitalWrite(PINKY, topDist < FAR ? HIGH : LOW);
}

void checkCliff() {
  // Adds Distance data to DiffBuffer and checks if there's a cliff
  bool topCliff = TopBuffer.push(theTopTFL.getDist());
  bool botCliff = BotBuffer.push(theBotTFL.getDist());
  if((topCliff || botCliff) && !buzzSpeaker) {
    // There is a cliff, start speakerTone
    Serial.println("THERE IS A CLIFF!!! --------------------------------");
    buzzSpeaker = true;
    speakerToneTimer.runNow(); // Async run to instantly let user know
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize buzz motors
  pinMode(POINTER, OUTPUT);
  pinMode(MIDDLE, OUTPUT);
  pinMode(RING, OUTPUT);
  pinMode(PINKY, OUTPUT);

  // Initialize speaker buzzer
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Run synchronous functionsx
  processDataTimer.run();
  speakerToneTimer.run();
}
