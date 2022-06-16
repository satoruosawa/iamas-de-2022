#include <M5Stack.h>

// アドレスなどのプログラム全体で変更がないものは #define を使って定義する。
// コンパイル時に#define で定義した名前が、すべて置き換えられる。
#define ADDRESS 0x52  // ジョイスティックのI2Cアドレスを定義

int x_data;
int y_data;
int button_data;

void setup() {
  M5.begin();
  Wire.begin();  // マスターとしてI2C通信を開始
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.println("Joystick Sample");
}

void loop() {
  // 3バイトのデータをスレーブデバイスにリクエスト
  Wire.requestFrom(ADDRESS, 3);
  if (Wire.available()) {  // スレーブからデータが帰ってきた場合の分岐
    x_data = Wire.read();
    y_data = Wire.read();
    button_data = Wire.read();

    M5.Lcd.setCursor(100, 50, 4);
    M5.Lcd.print("X:");
    M5.Lcd.print(x_data);
    M5.Lcd.print("      ");
    M5.Lcd.setCursor(100, 80, 4);
    M5.Lcd.print("Y:");
    M5.Lcd.print(y_data);
    M5.Lcd.print("      ");
    M5.Lcd.setCursor(100, 110, 4);
    M5.Lcd.print("B:");
    M5.Lcd.print(button_data);
    M5.Lcd.print("      ");
  }
  delay(10);
}