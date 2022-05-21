#include <M5Stack.h>

int number = 0;

void setup() { M5.begin(); }

void loop() {
  Serial.println(number);  // シリアル通信で文字列をPCへ送信
  number = number + 1;
  delay(1000);
}
