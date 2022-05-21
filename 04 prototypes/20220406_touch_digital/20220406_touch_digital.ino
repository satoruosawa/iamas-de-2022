#include <M5Stack.h>

const int TouchPin = 22;

int value = 0;

void setup() {
  M5.begin();
  // M5.Power.begin();  // ←この行を追加するとセンシングできない。
  pinMode(TouchPin, INPUT);
}

void loop() {
  value = digitalRead(TouchPin);
  Serial.println(value);
}