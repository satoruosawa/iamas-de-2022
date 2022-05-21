#include <M5Stack.h>

int value21 = 0;
int value22 = 0;

void setup() {
  M5.begin();
  // M5.Power.begin();  // ←この行を追加するとセンシングできない。
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  dacWrite(25, 0);
}

void loop() {
  value21 = digitalRead(21);
  value22 = digitalRead(22);
  Serial.print(value21);
  Serial.print(",");
  Serial.println(value22);
}