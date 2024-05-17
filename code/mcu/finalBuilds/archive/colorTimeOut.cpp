// colorTimeOut.cpp
// aiming to control the leds such that it they fade over time as opposed to suddenly cutting out / not getting stuck at their last state
// use millis to avoid halting the program or FreeRTOS
// change wiring to represent the 4 different layers that the pillars each have

// fully utilizing

// libs to build with

#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include "BluetoothA2DPSource.h"

// led pins
#define redPin 26
#define greenPin 25
#define bluePin 27

// initializing instances of I2S stream and A2DP sink passing i2s as a param
I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);
BluetoothA2DPSource a2dp_source;
// ^^ adding bluetooth source lib and instantiating it

TaskHandle_t ledControlHandle = NULL;
TaskHandle_t bluetoothConnectionHandle = NULL;

bool bluetoothConnection = false;

// led related
// creating a class for leds to be public and have its own dedicated function
class LedClass
{
    // initialising public variables/members to be used inside the class
public:
    int redValue;
    int greenValue;
    int blueValue;

    // constructor for the class
    LedClass(int red, int green, int blue) : redValue(red), greenValue(green), blueValue(blue) {}

    void setLedValuesVolume(int red, int green, int blue)
    {
        analogWrite(redPin, red);
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);
    }

    void setLedValuesConnection(int red, int green, int blue)
    {
        analogWrite(redPin, red);
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);
    }
};

// global instance of LedClass pillarLeds
LedClass pillarLeds(0, 0, 0);

void volumeCallback(int volume)
{
    // displaying volume
    Serial.println("Volume is now:  ");
    Serial.print(volume);

    // as the volume goes 0-127, multiply by 2 to roughly equalize it to 255 ratios
    // calling the setLedValues function in the class that pillarLeds is a child of

    pillarLeds.setLedValuesVolume(0, 0, (volume * 2));
};

// task to run actively in the background via multi core processing
void checkBluetoothConnectionTask(void *pvParameters)
{
    for (;;)
    {
        if (a2dp_sink.is_connected())
        {
            Serial.println("Bluetooth is connected.");

            // setting flag state to true, used to monitor repeat led colorings
            bluetoothConnection == true;

            // Set LED to green to indicate connection
            pillarLeds.setLedValuesConnection(0, 255, 0);
        }
        else
        {
            Serial.println("Bluetooth is not connected. Attempting to reconnect...");
            // Set LED to red to indicate disconnection
            pillarLeds.setLedValuesConnection(255, 0, 0);

            // Attempt to reconnect
            a2dp_sink.start("MyMusic");

            // Check connection status after attempting to reconnect
            if (a2dp_sink.is_connected())
            {
                Serial.println("Reconnected to Bluetooth successfully.");
                // Set LED to green to indicate successful reconnection
                pillarLeds.setLedValuesConnection(0, 255, 0);
            }
            else
            {
                Serial.println("Failed to reconnect to Bluetooth.");
                // Set LED to red to indicate failure
                pillarLeds.setLedValuesConnection(255, 0, 0);
            };
        };
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};

#pragma region setup
void audioStreamingSetup()
{
    // regular config for the audio transmission - more suitable for external DAC/ADC that does not require software tuning
    auto cfg = i2s.defaultConfig();
    cfg.pin_bck = 16;  // Bit clock
    cfg.pin_ws = 5;    // Stereo pin
    cfg.pin_data = 17; // Data transfer pin (esp to dac)

    i2s.begin(cfg); // filling in the class variable values and starting the stream

    // register the volume callback function
    a2dp_sink.set_on_volumechange(volumeCallback);

    // enable auto reconnect
    a2dp_sink.set_auto_reconnect(true);

    // creating bluetooth instantiation
    a2dp_sink.start("MyMusic");
};

void ledSetup()
{
    // rgb pin outputs being defined
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
};

// first func to call
void setup()
{
    // high baud rate to allow for debugging and faster communication
    Serial.begin(115200);

    // calls other setup functions
    audioStreamingSetup();
    ledSetup();
    xTaskCreate(checkBluetoothConnectionTask, "checkBluetoothConnectionTask", 10000, NULL, 1, &bluetoothConnectionHandle);
}
#pragma endregion setup

void loop()
{
}
