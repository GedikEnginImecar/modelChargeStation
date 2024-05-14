#include "Arduino.h"

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(2500);
    Serial.print("Delay by 2.5s");
    Serial.print("MOSI: ");
    Serial.println(MOSI);
    Serial.print("MISO: ");
    Serial.println(MISO);
    Serial.print("SCK: ");
    Serial.println(SCK);
    Serial.print("SS: ");
    Serial.println(SS);
}

void loop()
{
    // put your main code here, to run repeatedly:
}

// https://wokwi.com/projects/330669951756010068 example to look at
// EspSoftwareSerial by Dirk Kaar
// ESP32-audioI2S by schreibfaul1
// https: // github.com/pschatzmann/ESP32-A2DP/wiki

// look at how to send data, bit clock, lrc etc from esp32 i2s to either speakers or the dac
// https://www.youtube.com/watch?v=qNLvoSQCx60