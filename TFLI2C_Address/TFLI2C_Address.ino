#include <Arduino.h>
#include <Wire.h>
#include <TFLI2C.h>  // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t  tfAddr = 0x20;        // custom I2C address

void setup()
{
    Serial.begin( 115200);  // Initialize Serial port
    Wire.begin();           // Initialize Wire library

    while(!Serial); // Waits for Serial to start before printing

    bool switchRes = tflI2C.Set_I2C_Addr(tfAddr, TFL_DEF_ADR);
    if(!switchRes) Serial.println("Failed to switch address");
    else Serial.println("Switched Address");
}


void loop()
{
}
