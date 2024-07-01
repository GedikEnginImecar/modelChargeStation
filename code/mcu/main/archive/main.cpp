
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

// led related
// creating a class for leds to be public and have its own dedicated function
class LedClass
{
  // defining public variables to be used inside the pillarLeds class
public:
  int redValue;
  int greenValue;
  int blueValue;

  // constructor for the class
  LedClass(int red, int green, int blue) : redValue(red), greenValue(green), blueValue(blue) {}

  void setLedValues(int red, int green, int blue)
  {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
  }
};

// global
// global instance of LedClass pillarLeds
LedClass pillarLeds(0, 0, 0);

void volumeCallback(int volume)
{
  // displaying volume
  Serial.println("Volume is now:  ");
  Serial.print(volume);

  // as the volume goes 0-127, multiply by 2 to roughly equalize it to 255 ratios
  // calling the setLedValues function in the class that pillarLeds is a child of
  pillarLeds.setLedValues(0, 0, (volume * 2));
};

void checkBluetoothConnection()
{
  if (a2dp_sink.is_connected())
  {
    Serial.println("Bluetooth is connected.");
    // Set LED to green to indicate connection
    pillarLeds.setLedValues(0, 255, 0);
  }
  else
  {
    Serial.println("Bluetooth is not connected. Attempting to reconnect...");
    // Set LED to red to indicate disconnection
    pillarLeds.setLedValues(255, 0, 0);

    // Attempt to reconnect
    a2dp_sink.start("MyMusic");

    // Check connection status after attempting to reconnect
    if (a2dp_sink.is_connected())
    {
      Serial.println("Reconnected to Bluetooth successfully.");
      // Set LED to green to indicate successful reconnection
      pillarLeds.setLedValues(0, 255, 0);
    }
    else
    {
      Serial.println("Failed to reconnect to Bluetooth.");
      // Set LED to red to indicate failure
      pillarLeds.setLedValues(255, 0, 0);
    };
  };
}

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
  checkBluetoothConnection();
}

void loop()
{
  checkBluetoothConnection();
  delay(2500);
}
