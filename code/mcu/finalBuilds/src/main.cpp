#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

#define redPin 25
#define greenPin 26
#define bluePin 27

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void setup()
{
  Serial.begin(9600);

  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = 16;
  cfg.pin_ws = 5;
  cfg.pin_data = 17;
  i2s.begin(cfg);

  a2dp_sink.start("MyMusic");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  delay(500);
  Serial.println("red");
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  delay(500);
  Serial.println("green");
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);

  delay(500);
  Serial.println("blue");
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}
