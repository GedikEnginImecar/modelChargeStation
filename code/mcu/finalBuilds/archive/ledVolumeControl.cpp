// libs to build with

#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

// led pins
#define redPin 25
#define greenPin 26
#define bluePin 27

// initializing instances of I2S stream and A2DP sink passing i2s as a param
I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void setLed(int volume)
{
    delay(500);
    Serial.println("shift");
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);

    delay(500);
    Serial.println("updated volume");
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, volume);
};

void volumeMonitoring(int volume)
{
    Serial.print("Volume is now:  ");
    Serial.print(volume);
    setLed(volume);
};

void audioStreamingSetup()
{
    // regular config for the audio transmission - more suitable for external DAC/ADC that does not require software tuning
    auto cfg = i2s.defaultConfig();
    cfg.pin_bck = 16;  // Bit clock
    cfg.pin_ws = 5;    // Stereo pin
    cfg.pin_data = 17; // Data transfer pin (esp to dac)
    i2s.begin(cfg);    // filling in the class variable values and starting the stream

    // register the volume callback function
    a2dp_sink.set_on_volumechange(volumeMonitoring);

    a2dp_sink.start("MyMusic"); // creating bluetooth instantiation
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
}

void loop()
{
    // nothing to be seen here folks
}
