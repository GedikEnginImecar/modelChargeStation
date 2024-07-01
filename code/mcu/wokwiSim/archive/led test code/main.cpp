#include <Arduino.h>

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

void setLayerColor(ledLayer layer, int red, int green, int blue)
{
    analogWrite(layer.redPin, red);
    analogWrite(layer.greenPin, green);
    analogWrite(layer.bluePin, blue);
}

void setup()
{
    Serial.begin(115200);
    pinOutputSetup();
}

void loop()
{
    setLayerColor(layer1, 255, 0, 0);
    setLayerColor(layer2, 255, 0, 0);
    setLayerColor(layer3, 255, 0, 0);
    setLayerColor(layer4, 255, 0, 0);

    delay(500);

    setLayerColor(layer1, 0, 255, 0);
    setLayerColor(layer2, 0, 255, 0);
    setLayerColor(layer3, 0, 255, 0);
    setLayerColor(layer4, 0, 255, 0);

    delay(500);

    setLayerColor(layer1, 255, 0, 0);
    setLayerColor(layer2, 255, 0, 0);
    setLayerColor(layer3, 255, 0, 0);
    setLayerColor(layer4, 255, 0, 0);

    delay(500);

    setLayerColor(layer1, 255, 255, 0);
    setLayerColor(layer2, 255, 255, 0);
    setLayerColor(layer3, 255, 255, 0);
    setLayerColor(layer4, 255, 255, 0);

    delay(500);

    setLayerColor(layer1, 0, 255, 255);
    setLayerColor(layer2, 0, 255, 255);
    setLayerColor(layer3, 0, 255, 255);
    setLayerColor(layer4, 0, 255, 255);

    delay(500);

    setLayerColor(layer1, 255, 0, 255);
    setLayerColor(layer2, 255, 0, 255);
    setLayerColor(layer3, 255, 0, 255);
    setLayerColor(layer4, 255, 0, 255);

    delay(500);

    setLayerColor(layer1, 0, 0, 0);
    setLayerColor(layer2, 0, 0, 0);
    setLayerColor(layer3, 0, 0, 0);
    setLayerColor(layer4, 0, 0, 0);
}
