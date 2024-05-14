#include "Arduino.h"
#include "I2S.h"
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink(I2S);

void setup()
{
    I2S.setSckPin(5);
    I2S.setFsPin(17);
    I2S.setDataPin(16);
    if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16))
    {
        Serial.println("Failed to initialize I2S!");
        while (1)
            ; // do nothing
    }

    a2dp_sink.start("MyMusic");
}

void loop()
{
}
