// rebuiltFreeRTOS.cpp
// rebuilding the code to help with clarity and implement KISS and SOLID software development principles
// easier to work and create a FreeRTOS and general script based on a cleaned up and refined version of the previous project

#pragma region libs

#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include "BluetoothA2DPSource.h"

#pragma endregion libs

#pragma region ledPins

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

#pragma endregion ledPins

#pragma region instanceCreation

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);
BluetoothA2DPSource a2dp_source;

#pragma endregion instanceCreation

#pragma region taskHandlers

TaskHandle_t ledControlHandle = NULL;
TaskHandle_t bluetoothConnectionHandle = NULL;

#pragma endregion taskHandlers

#pragma region globalObjects

bool bluetoothConnection = false;

const int layerRedPins[] = {33, 27, 22, 18};
const int layerGreenPins[] = {25, 14, 23, 19};
const int layerBluePins[] = {32, 26, 13, 4};

#pragma endregion globalObjects

// Parent class for managing LEDs
class Leds
{
public:
    // Constructor
    Leds() {}

protected:
    // Function to set RGB color for a specific layer by index
    void setLayerColor(int layerIndex, int redValue, int greenValue, int blueValue)
    {
        if (layerIndex >= 1 && layerIndex <= 4)
        {
            analogWrite(layerRedPins[layerIndex - 1], redValue);
            analogWrite(layerGreenPins[layerIndex - 1], greenValue);
            analogWrite(layerBluePins[layerIndex - 1], blueValue);
        }
    }

    // Function to set RGB color for all layers
    void setAllColor(int redValue, int greenValue, int blueValue)
    {
        for (int layer = 1; layer <= 4; ++layer)
        {
            setLayerColor(layer, redValue, greenValue, blueValue);
        }
    }

    // Function to turn off all LEDs
    void turnOffAll()
    {
        setAllColor(0, 0, 0);
    }

    // Function to set LED color for layer1 and layer4
    void testFunction1()
    {
        setLayerColor(1, 0, 0, 255); // Set layer1 to blue
        setLayerColor(4, 255, 0, 0); // Set layer4 to red
    }

    // Function to perform connection test sequence
    void testFunction2()
    {
        // Iterate through each layer with a 500ms pause between each layer
        for (int layer = 1; layer <= 4; ++layer)
        {
            setLayerColor(layer, 255, 0, 0); // Set current layer LEDs to red
            Serial.print("Layer ");
            Serial.print(layer);
            Serial.println(" LEDs set to Red");
            delay(500); // Wait for 500ms

            setLayerColor(layer, 255, 255, 0); // Set current layer LEDs to yellow
            Serial.print("Layer ");
            Serial.print(layer);
            Serial.println(" LEDs set to Yellow");
            delay(500); // Wait for 500ms
        }
        turnOffAll(); // Turn off all LEDs after sequence
        Serial.println("All LEDs turned off");
    }
};

#pragma region ledSubclasses
// Subclass for Layer 1 LEDs
class Layer1Leds : public Leds
{
public:
    Layer1Leds() {}
};

// Subclass for Layer 2 LEDs
class Layer2Leds : public Leds
{
public:
    Layer2Leds() {}
};

// Subclass for Layer 3 LEDs
class Layer3Leds : public Leds
{
public:
    Layer3Leds() {}
};

// Subclass for Layer 4 LEDs
class Layer4Leds : public Leds
{
public:
    Layer4Leds() {}
};

#pragma endregion ledSubclasses

class BluetoothManager
{
public:
    // variables within BluetoothManager - public as there aren't any
    // children inheriting to declare as public to allow access externally
    BluetoothManager()
    {
        bluetoothConnection = false;
    }

    // to check the state of the BT connection and manipulate the flags and initiate led changes
    void checkBluetoothConnection()
    {
        // code in here
    }

    // playback setup and audio level monitoring
    void audioStreamingSetup()
    {
        // code in here
    }

    // function to call led changes based on the audio levels
    void volumeCallback()
    {
        // code in here
    }
};

// Main function
void setup()
{
    // Initialize serial communication at 115200 baud rate
    Serial.begin(115200);

    // Create instances of each layer subclass
    Layer1Leds layer1;
    Layer2Leds layer2;
    Layer3Leds layer3;
    Layer4Leds layer4;

    // Example usage
    // layer1.testFunction1();   // Set layer1 to blue, layer4 to red
    // layer1.testFunction2(); // Perform connection test sequence on layer1 LEDs
}

void loop()
{
    // Nothing in loop for this example
}