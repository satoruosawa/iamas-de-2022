#include <M5Stack.h>

#define ADC_ADDRESS 0x50
#define JOYSTICK_ADDRESS 0x52

unsigned int adc_value = 0;
int x_data;
int y_data;
int button_data;

void setup() {
  M5.begin();
  Wire.begin();
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.println("Joystick and ADC");
}

void loop() {
  Wire.requestFrom(JOYSTICK_ADDRESS, 3);
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
  Wire.requestFrom(ADC_ADDRESS, 2);
  if (Wire.available()) {
    adc_value = (Wire.read() & 0x0f) << 8;
    adc_value |= Wire.read();

    M5.Lcd.setCursor(100, 140, 4);
    M5.Lcd.print("ADC:");
    M5.Lcd.print(adc_value);
    M5.Lcd.print("      ");
  }

  Serial.print(x_data);
  Serial.print(",");
  Serial.print(y_data);
  Serial.print(",");
  Serial.print(button_data);
  Serial.print(",");
  Serial.println(adc_value);

  delay(10);
}