/* File Name: TFLI2C_simple.ino
 * Developer: Bud Ryerson
 * Date:      4 NOV 2021
 * Version:   0.1.2
 * Described: Simplified Arduino example sketch for the Benewake
 *            TF-Luna LiDAR sensor configured for the I2C interface
 */
 
#include <Arduino.h>     // every sketch needs this
#include <Wire.h>        // instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.2.0

#define Noise1 4
#define Noise2 5
#define Noise3 6
#define Noise4 7

TFLI2C tflI2C;

int16_t  tfDist;    // distance in centimeters
int16_t  tfAddr = TFL_DEF_ADR;  // use this default I2C address or
                                // set variable to your own value

void setup()
{
    Serial.begin( 115200);  // initialize serial port

    // Software USB for Micro
    while (!Serial);
    // END
    Wire.begin();           // initialize Wire library
    Serial.println( "TFLI2C example code simplified"); // say "Hello!"
    Serial.println( "4 NOV 2021");                     // and add date
    Serial.println(TFL_DEF_ADR, HEX);

    pinMode(Noise1, OUTPUT);
    pinMode(Noise2, OUTPUT);
    pinMode(Noise3, OUTPUT);
    pinMode(Noise4, OUTPUT);
}

void loop()
{
    if( tflI2C.getData( tfDist, tfAddr)) // If read okay...
    {
        Serial.print("Dist: ");
        Serial.println(tfDist);          // print the data...
        //add logic here
        
  if (tfDist < 25){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, HIGH);
  digitalWrite(Noise3, HIGH);
  digitalWrite(Noise4, HIGH);
  }
  
  else if (tfDist < 50){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, HIGH);
  digitalWrite(Noise3, HIGH);
  digitalWrite(Noise4, LOW);
  }
  
   else if (tfDist < 75){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, HIGH);
  digitalWrite(Noise3, LOW);
  digitalWrite(Noise4, LOW);
   }

    else if (tfDist< 100){
  digitalWrite(Noise1, HIGH);
  digitalWrite(Noise2, LOW);
  digitalWrite(Noise3, LOW);
  digitalWrite(Noise4, LOW);
    }
    else {
  digitalWrite(Noise1, LOW);
  digitalWrite(Noise2, LOW);
  digitalWrite(Noise3, LOW);
  digitalWrite(Noise4, LOW);
    }
  
    }
    else {
      tflI2C.printStatus();           // else, print error.
      Serial.print("\n");
    }

    delay( 50);
}
