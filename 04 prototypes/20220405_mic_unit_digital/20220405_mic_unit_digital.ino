#include <M5Stack.h>

int value = 0;

void setup() {
  M5.begin();
  // M5.Power.begin();  // ←この行を追加するとセンシングできない。
  pinMode(21, INPUT);
  dacWrite(25, 0);
}

void loop() {
  value = digitalRead(21);
  Serial.println(value);
}