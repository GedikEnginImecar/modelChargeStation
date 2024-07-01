#include <Arduino.h>

// Contoh Code Button dan LED
int ledPin_1 = 15; // Pin LED
int ledPin_2 = 4;
int pushButton_1 = 14; // Pin Button
int pushButton_2 = 12; // Pin Button
int state_btn_1 = 0;   // Status btn ( Boolean )
int state_btn_2 = 0;   // Status btn ( Boolean )

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin_1, OUTPUT);
  pinMode(pushButton_1, INPUT);
  pinMode(ledPin_2, OUTPUT);
  pinMode(pushButton_2, INPUT);
}

void loop()
{
  state_btn_1 = digitalRead(pushButton_1);
  state_btn_2 = digitalRead(pushButton_2);

  if (state_btn_1 == HIGH && state_btn_2 == LOW)
  {
    digitalWrite(ledPin_1, HIGH);
    Serial.println("LED 1");
  }
  if (state_btn_2 == HIGH && state_btn_1 == LOW)
  {
    digitalWrite(ledPin_2, HIGH);
    Serial.println("LED 2");
  }
  else
  {
    digitalWrite(ledPin_1, LOW);
    digitalWrite(ledPin_2, LOW);
  }
}
