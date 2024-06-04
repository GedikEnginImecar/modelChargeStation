// rebuiltMain.cpp
// post brief CPP learning and small project

#pragma region libs

#include "Arduino.h"             // defsault Arduino library
#include "AudioTools.h"          // audio playback
#include "BluetoothA2DPSink.h"   // advanced audio distribution player lib
#include "BluetoothA2DPSource.h" // advanved audio distribution source lib

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

struct ledLayer
{
    int redPin;
    int greenPin;
    int bluePin;
};

ledLayer layer1 = {layer1RedPin, layer1GreenPin, layer1BluePin};
ledLayer layer2 = {layer2RedPin, layer2GreenPin, layer2BluePin};
ledLayer layer3 = {layer3RedPin, layer3GreenPin, layer3BluePin};
ledLayer layer4 = {layer4RedPin, layer4GreenPin, layer4BluePin};

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

#pragma endregion globalObjects

#pragma region functionDeclarations

void setLayerColor(ledLayer layer, int red, int green, int blue);
void setLedsOff(std::string layerList[]);
void pinOutputSetup();
void audioSetup();
void volumeCallback(int volume);
void bluetoothConnectionTask(void *parameters);

#pragma endregion functionDeclarations

// bluetooth
// TODO: create bluetooth server
// TODO: allow users to connect to bluetooth server
// TODO: volume reading from bluetooth and output (in terminal)
// TODO: auto reconnect?

// LEDS
// TODO: function to control leds
// TODO: reflect status when no connection
// TODO: reflect status when connected
// TODO: reflect volume level (volume level x2)
// TODO: algorithm to help make leds fade

void setup()
{
    Serial.begin(115200);
    pinOutputSetup();
    audioSetup();
    xTaskCreate(bluetoothConnectionTask, "bluetoothConnectionTask", 10000, NULL, 1, &bluetoothConnectionHandle);
}

void loop()
{
}

#pragma region setupMethods

void pinOutputSetup()
{
    pinMode(layer1.redPin, OUTPUT);
    pinMode(layer1.greenPin, OUTPUT);
    pinMode(layer1.bluePin, OUTPUT);
    pinMode(layer2.redPin, OUTPUT);
    pinMode(layer2.greenPin, OUTPUT);
    pinMode(layer2.bluePin, OUTPUT);
    pinMode(layer3.redPin, OUTPUT);
    pinMode(layer3.greenPin, OUTPUT);
    pinMode(layer3.bluePin, OUTPUT);
    pinMode(layer4.redPin, OUTPUT);
    pinMode(layer4.greenPin, OUTPUT);
    pinMode(layer4.bluePin, OUTPUT);
}

void audioSetup()
{
    auto cfg = i2s.defaultConfig();

    cfg.pin_bck = 16;  // Bit clock
    cfg.pin_ws = 5;    // Stereo pin
    cfg.pin_data = 17; // Data transfer pin (esp to dac)

    i2s.begin(cfg);

    a2dp_sink.set_on_volumechange(volumeCallback);
    a2dp_sink.set_auto_reconnect(true);
    a2dp_sink.start("MyMusic");
}

#pragma endregion setupMethods

#pragma region regularMethods

void volumeCallback(int volume)
{
    // displaying volume
    Serial.println("Volume is now:  ");
    Serial.print(volume);
    int trueVolume = volume * 2;

    // as the volume goes 0-127, multiply by 2 to roughly equalize it to 255 normal

    if (volume == 0)
    {
        ledLayer layers[] = {layer1, layer2, layer3, layer4};
        setLedsOff(layers);
    }
    else if (volume > 0)
    {
        setLayerColor(layer1, 0, 0, volume * 8);
    }
    else if (volume > 32)
    {
        setLayerColor(layer1, 0, 0, volume * 8);
        setLayerColor(layer2, 0, 0, volume * 4);
    }
    else if (volume > 64)
    {
        setLayerColor(layer1, 0, 0, volume * 8);
        setLayerColor(layer2, 0, 0, volume * 4);
        setLayerColor(layer3, 0, 0, volume * 2 / 6);
    }
    else if (volume > 96)
    {
        setLayerColor(layer1, 0, 0, volume * 8);
        setLayerColor(layer2, 0, 0, volume * 4);
        setLayerColor(layer3, 0, 0, volume * 2);
    }
};

void setLayerColor(ledLayer layer, int red, int green, int blue)
{
    analogWrite(layer.redPin, red);
    analogWrite(layer.greenPin, green);
    analogWrite(layer.bluePin, blue);
}

void setLedsOff(ledLayer layerList[])
{
    for (int i = 0; i < (sizeof(layerList) / sizeof(layerList[0])); i++)
    {
        setLayerColor(layerList[i], 0, 0, 0);
    }
}

#pragma endregion regularMethods

#pragma region taskMethods

void bluetoothConnectionTask(void *pvParameters)
{
    for (;;)
    {
        if (a2dp_sink.is_connected())
        {
            Serial.println("Bluetooth is connected.");

            // setting flag state to true, used to monitor repeat led colorings
            bluetoothConnection == true;

            // Set LED to green to indicate connection
            setLayerColor(layer1, 0, 255, 0);
            setLayerColor(layer2, 0, 255, 0);
            setLayerColor(layer3, 0, 255, 0);
            setLayerColor(layer4, 0, 255, 0);
        }
        else
        {
            Serial.println("Bluetooth is not connected. Attempting to reconnect...");
            // Set LED to red to indicate disconnection
            setLayerColor(layer1, 255, 0, 0);
            setLayerColor(layer2, 255, 0, 0);
            setLayerColor(layer3, 255, 0, 0);
            setLayerColor(layer4, 255, 0, 0);

            // Attempt to reconnect
            a2dp_sink.start("MyMusic");

            // Check connection status after attempting to reconnect
            if (a2dp_sink.is_connected())
            {
                Serial.println("Reconnected to Bluetooth successfully.");
                // Set LED to green to indicate successful reconnection

                setLayerColor(layer1, 0, 255, 0);
                setLayerColor(layer2, 0, 255, 0);
                setLayerColor(layer3, 0, 255, 0);
                setLayerColor(layer4, 0, 255, 0);
            }
            else
            {
                Serial.println("Failed to reconnect to Bluetooth.");
                // Set LED to red to indicate failure
                setLayerColor(layer1, 255, 0, 0);
                setLayerColor(layer2, 255, 0, 0);
                setLayerColor(layer3, 255, 0, 0);
                setLayerColor(layer4, 255, 0, 0);
            };
        };
        vTaskDelay(2500 / portTICK_PERIOD_MS);
    }
}

#pragma endregion taskMethods