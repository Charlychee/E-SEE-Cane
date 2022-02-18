/* File Name: TFLI2C_example.ino
 * Developer: Bud Ryerson
 * Date:      4 NOV 2021
 * Version:   0.1.1 - Changed the default TFL_DEFAULT_ADDR and
              TFL_DEFAULT_FPS to TFL_DEF_ADR and TFL_DEF_FPS.
              0.1.2 - Fixed typos in  comments
 * Described: Arduino example sketch for the Benewake TF-Luna
 *            LiDAR sensor configured for the I2C interface
 */
 
#include <Arduino.h>
#include <Wire.h>
#include <TFLI2C.h>  // TFLuna-I2C Library v.0.2.0

TFLI2C tflI2C;

// Use these defaults or insert your own values
int16_t  tfAddr = 0x20;    // I2C address
uint16_t tfFrame = TFL_DEF_FPS;   // default frame rate

// device variables passed back by getData
int16_t  tfDist = 0 ;   // distance in centimeters
int16_t  tfFlux = 0 ;   // signal quality in arbitrary units
int16_t  tfTemp = 0 ;   // temperature in 0.01 degree Celsius

// other device variables
uint16_t tfTime = 0;    // device clock in milliseconds
uint8_t  tfVer[3];      // device version number
uint8_t  tfCode[14];    // device serial number

// sub-loop counter for Time display
uint8_t tfCount = 0;

void setup()
{
    Serial.begin( 115200);  // Initialize Serial port
    Wire.begin();           // Initialize Wire library
}

void loop()
{
    // If data is read without error...
    if( tflI2C.getData( tfDist, tfFlux, tfTemp, tfAddr))
    {
        Serial.print("Dist: ");      // ...print distance,
        Serial.print(tfDist);
        Serial.print(" | Certainty: ");   // ...print quality
        Serial.print(tfFlux);

        // Convert temperature from hundredths
        // of a degree to a whole number and...
        tfTemp = int16_t( tfTemp / 100);

        Serial.print(" | Temp: ");     // ...print temperature.
        Serial.println( tfTemp);
    }
    else tflI2C.printStatus();        // else, print error status.

    // Every ten loops, this prints device time
    // in milliseconds and resets the counter.
    if( tfCount < 10) ++tfCount;
    else
    {
        Serial.print( "Get Time: ");
        tflI2C.Get_Time( tfTime, tfAddr);
        Serial.println(  tfTime);
        tfCount = 0;
    }

    delay( 50);
}
