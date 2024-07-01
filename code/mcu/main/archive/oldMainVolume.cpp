#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

#define redPin 25
#define greenPin 26
#define bluePin 27

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

// Callback function to handle volume changes
void volumeCallback(int volume)
{
    Serial.print("Volume changed: ");
    Serial.println(volume);
}

void setup()
{
    Serial.begin(115200);

    auto cfg = i2s.defaultConfig();
    cfg.pin_bck = 16;
    cfg.pin_ws = 5;
    cfg.pin_data = 17;
    i2s.begin(cfg);

    // Register the volume callback function
    a2dp_sink.set_on_volumechange(volumeCallback);

    a2dp_sink.start("MyMusic");

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop()
{
    Serial.println("test");
    delay(1000);
}
