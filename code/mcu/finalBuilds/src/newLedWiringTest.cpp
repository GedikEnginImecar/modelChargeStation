#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include "BluetoothA2DPSource.h"

#define layer1RedPin 33
#define layer1GreenPin 25
#define layer1BluePin 32

#define layer2RedPin 27
#define layer2GreenPin 14
#define layer2BluePin 26

#define layer3RedPin 22
#define layer3GreenPin 23
#define layer3BluePin 13

#define layer4RedPin 18
#define layer4GreenPin 19
#define layer4BluePin 4

void setColor(int redPin, int greenPin, int bluePin, const char *layerName)
{
    Serial.print("Setting colors for ");
    Serial.println(layerName);

    // Set the pins to Red
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    Serial.println("Red");
    delay(1000); // 1 second delay

    // Set the pins to Green
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    Serial.println("Green");
    delay(1000); // 1 second delay

    // Set the pins to Blue
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
    Serial.println("Blue");
    delay(1000); // 1 second delay
}

void setup()
{
    // Initialize all pins as OUTPUT
    pinMode(layer1RedPin, OUTPUT);
    pinMode(layer1GreenPin, OUTPUT);
    pinMode(layer1BluePin, OUTPUT);

    pinMode(layer2RedPin, OUTPUT);
    pinMode(layer2GreenPin, OUTPUT);
    pinMode(layer2BluePin, OUTPUT);

    pinMode(layer3RedPin, OUTPUT);
    pinMode(layer3GreenPin, OUTPUT);
    pinMode(layer3BluePin, OUTPUT);

    pinMode(layer4RedPin, OUTPUT);
    pinMode(layer4GreenPin, OUTPUT);
    pinMode(layer4BluePin, OUTPUT);

    // Initialize Serial communication
    Serial.begin(9600);
    while (!Serial)
    {
        ; // Wait for Serial port to connect
    }
}

void loop()
{
    // Cycle through RGB colors for all layers
    setColor(layer1RedPin, layer1GreenPin, layer1BluePin, "Layer 1");
    setColor(layer2RedPin, layer2GreenPin, layer2BluePin, "Layer 2");
    setColor(layer3RedPin, layer3GreenPin, layer3BluePin, "Layer 3");
    setColor(layer4RedPin, layer4GreenPin, layer4BluePin, "Layer 4");
}
