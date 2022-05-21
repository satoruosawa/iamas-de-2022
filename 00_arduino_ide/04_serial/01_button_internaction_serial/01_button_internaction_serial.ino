#include <M5Stack.h>

void setup() { M5.begin(); }

void loop() {
  M5.update();  // buttonを使うときはこの行を追加

  // M5.BtnX.isPressed()は、ボタンが押されている間trueを返す。
  int button_a = M5.BtnA.isPressed();
  int button_b = M5.BtnB.isPressed();
  int button_c = M5.BtnC.isPressed();

  Serial.print(button_a);
  Serial.print(",");
  Serial.print(button_b);
  Serial.print(",");
  Serial.println(button_c);

  delay(10);
}
