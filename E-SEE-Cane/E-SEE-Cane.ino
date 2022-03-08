// Author: Charles Lee - ccl002@ucsd.edu
// The main program for the E-SEE-Cane project

#include <Wire.h>
#include "TFLWrapper.h"
#include "Timer.h"
#include "DiffBuffer.h"

// TFL Sensors
#define TFL_TOP_ADDRESS 0x10
#define TFL_BOT_ADDRESS 0x20

// Buzzer Motor Pins
// pointer - yellow
// middle - red
// ring - gray
// orange - pinky
#define POINTER 4
#define MIDDLE 5
#define RING 6
#define PINKY 7

// Distance thresholds in centimeters
#define NEAR 50
#define FAR 100

// Cliff detection parameters
#define CLIFF_THRESH 50
#define BUZZER_PIN 9

// TF-Luna interface
TFLWrapper theTopTFL(TFL_TOP_ADDRESS);
TFLWrapper theBotTFL(TFL_BOT_ADDRESS);

// Buffer for cliff detection
DiffBuffer<50> TopBuffer(CLIFF_THRESH);
DiffBuffer<50> BotBuffer(CLIFF_THRESH);

// For buzzing the speaker on cliff detection
bool buzzSpeaker = false;

void processData() {
  // Retrieves data from sensors and push information to hardware
  theTopTFL.checkData();
  theBotTFL.checkData();
  
  Serial.print("TOP: ");
  Serial.print(theTopTFL.getDist());
  Serial.print(", BOT: ");
  Serial.println(theBotTFL.getDist());

  // Notify user based on data
  buzzMotor(theTopTFL.getDist(), theBotTFL.getDist());
  checkCliff();
}

void speakerTone() {
  // Buzzes the speaker tone if cliff detected, stops if not detected
  if (buzzSpeaker) {
    tone(BUZZER_PIN, 1000);
    buzzSpeaker = false;
  }
  else {
    noTone(BUZZER_PIN);
  }
}

Timer processDataTimer(100, &processData);
Timer speakerToneTimer(2000, &speakerTone);

void buzzMotor(int16_t topDist, int16_t botDist) {
  // Buzzes the motors based on the distance seen by sensors
  // Pointer and middle for bottom sensor
  // Ring and pinky for top sensor
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
    buzzSpeaker = true;
    speakerToneTimer.runNow(); // Async run to instantly let user know
  }
}

void setup() {
  Serial.begin(115200);
  while(!Serial); // Waits for Serial to start before printing

  // Start reading I2C
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
  // Run synchronous functions
  processDataTimer.run();
  speakerToneTimer.run();
}
