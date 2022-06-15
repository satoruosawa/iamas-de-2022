#include <M5Stack.h>

int volume = 1;

void setup() {
  M5.begin();
  M5.Speaker.setVolume(volume);  // スピーカーのボリュームを設定 範囲は 0 ~ 10
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    volume--;
    volume = constrain(volume, 0, 10);  // ボリュームの値を0 ~ 10に制限
    M5.Speaker.setVolume(volume);  // スピーカーのボリュームを設定
  }
  if (M5.BtnB.wasPressed()) {
    M5.Speaker.tone(3520, 40);
  }
  if (M5.BtnC.wasPressed()) {
    volume++;
    volume = constrain(volume, 0, 10);  // ボリュームの値を0 ~ 10に制限
    M5.Speaker.setVolume(volume);  // スピーカーのボリュームを設定
  }

  M5.Lcd.setCursor(70, 100);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Volume = ");
  M5.Lcd.print(volume);
  M5.Lcd.print(" ");
}
