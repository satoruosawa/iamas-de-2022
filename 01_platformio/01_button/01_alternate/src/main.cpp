#include <M5Stack.h>

bool button_a_state = false;
bool button_b_state = false;
bool button_c_state = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();  // buttonを使うときはこの行を追加

  // ボタンAの処理
  if (M5.BtnA.wasPressed()) {
    button_a_state = !button_a_state;
    if (button_a_state) {
      M5.Lcd.fillRect(0, 0, 100, 240, WHITE);
    } else {
      M5.Lcd.fillRect(0, 0, 100, 240, BLACK);
    }
  }

  // ボタンBの処理
  if (M5.BtnB.wasPressed()) {
    button_b_state = !button_b_state;
    if (button_b_state) {
      M5.Lcd.fillRect(110, 0, 100, 240, WHITE);
    } else {
      M5.Lcd.fillRect(110, 0, 100, 240, BLACK);
    }
  }

  // ボタンCの処理
  if (M5.BtnC.wasPressed()) {
    button_c_state = !button_c_state;
    if (button_c_state) {
      M5.Lcd.fillRect(220, 0, 100, 240, WHITE);
    } else {
      M5.Lcd.fillRect(220, 0, 100, 240, BLACK);
    }
  }

  delay(100);
}
