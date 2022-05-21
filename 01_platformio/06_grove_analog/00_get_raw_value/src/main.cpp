#include <M5Stack.h>

#define ADC_ADDRESS 0x50
unsigned int value = 0;

void setup() {
  M5.begin();
  Wire.begin();
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.println("ADC Sample");
}

void loop() {
  Wire.requestFrom(ADC_ADDRESS, 2);
  if (Wire.available()) {
    value = (Wire.read() & 0x0f) << 8;
    value |= Wire.read();

    M5.Lcd.setCursor(100, 50, 4);
    M5.Lcd.print("Value:");
    M5.Lcd.print(value);
    M5.Lcd.print("      ");

    Serial.println(value);
  }
  delay(10);
}