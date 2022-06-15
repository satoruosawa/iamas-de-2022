#include <M5Stack.h>

#define ADC_ADDRESS 0x50

unsigned int raw_value;
long value;
long abs_value;
long neutral_value = 1095;  // 無音時の値を設定

// 指数移動平均用の変数
long avg_value;                       // 平均値
long prev_avg_value = neutral_value;  // 一つ前のループの平均値
const float alpha = 0.2;              // 平滑化係数

void setup() {
  M5.begin();
  Wire.begin();
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.println("MIC amplitude");
}

void loop() {
  Wire.requestFrom(ADC_ADDRESS, 2);
  if (Wire.available()) {
    raw_value = (Wire.read() & 0x0f) << 8;
    raw_value |= Wire.read();

    // abs関数を用いて絶対値を計算
    abs_value = abs((long)raw_value - neutral_value);

    // 指数移動平均の計算
    // https://ja.wikipedia.org/wiki/%E7%A7%BB%E5%8B%95%E5%B9%B3%E5%9D%87#%E6%8C%87%E6%95%B0%E7%A7%BB%E5%8B%95%E5%B9%B3%E5%9D%87
    avg_value = abs_value * alpha + prev_avg_value * (1 - alpha);
    prev_avg_value = avg_value;

    M5.Lcd.setCursor(100, 50, 4);
    M5.Lcd.print("Raw Value:");
    M5.Lcd.print(raw_value);
    M5.Lcd.print("      ");
    M5.Lcd.setCursor(100, 80, 4);
    M5.Lcd.print("ABS Value:");  // 絶対値
    M5.Lcd.print(abs_value);
    M5.Lcd.print("      ");
    M5.Lcd.setCursor(100, 110, 4);
    M5.Lcd.print("AVG Value:");  // 指数移動平均値
    M5.Lcd.print(avg_value);
    M5.Lcd.print("      ");

    Serial.print(raw_value);
    Serial.print(",");
    Serial.print(abs_value);
    Serial.print(",");
    Serial.println(avg_value);
  }
  delay(10);
}