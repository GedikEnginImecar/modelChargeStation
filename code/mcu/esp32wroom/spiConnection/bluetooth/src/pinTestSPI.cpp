#include "Arduino.h"

void setup()
{
  // put your setup code here, to run once:
  delay(2500);
  Serial.print("Delay by 2.5s");
  Serial.begin(9600);
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);
}

void loop()
{
  // put your main code here, to run repeatedly:
}