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

// first func to call
void setup()
{
  // high baud rate to allow for debugging and faster communication
  Serial.begin(115200);

  // regular config for the audio transmission - more suitable for external DAC/ADC that does not require software tuning
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = 16;  // Bitclock
  cfg.pin_ws = 5;    // Stereo pin
  cfg.pin_data = 17; // Data transfer pin (esp to dac)
  i2s.begin(cfg);    // filling in the class variable values and starting the stream

  a2dp_sink.start("MyMusic"); // creating bluetooth instantiation

  // rgb pin outputs being defined
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  // basic cycling - should either use multithreading to not interrupt audio transmission or use millis to create a timer loop as opposed to delaying the entire program
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
