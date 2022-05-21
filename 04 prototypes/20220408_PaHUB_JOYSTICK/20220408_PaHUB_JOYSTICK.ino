#include <M5Stack.h>

#include "ClosedCube_TCA9548A.h"

#define FRONT 2

#define X_LOCAL 100
#define Y_LOCAL 35
#define X_OFFSET 160
#define Y_OFFSET 34

#define PaHub_I2C_ADDRESS 0x70

ClosedCube::Wired::TCA9548A tca9548a;

void setup() {
  M5.begin();
  M5.Power.begin();
  tca9548a.address(PaHub_I2C_ADDRESS);  // Set the I2C address.  设置I2C地址
  M5.Lcd.setTextFont(4);
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.setTextColor(YELLOW, TFT_BLACK);
  M5.Lcd.println(("PaHUB Example"));
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
}

char data[100];

void loop() {
  uint8_t returnCode = 0;
  uint8_t address;
  // ポートとchannelがずれてる？
  returnCode = tca9548a.selectChannel(0);

  Wire.requestFrom(0x52, 3);
  static uint8_t x_data, y_data, button_data;
  if (Wire.available()) {  // If data is received.  如果接收到数据
    x_data = Wire.read();
    y_data = Wire.read();
    button_data = Wire.read();
    sprintf(data, "x:%d y:%d button:%d\n", x_data, y_data, button_data);
    Serial.print(data);

    M5.Lcd.setCursor(100, 50, 4);
    M5.Lcd.printf("X:%d      ", x_data);
    M5.Lcd.setCursor(100, 80, 4);
    M5.Lcd.printf("Y:%d      ", y_data);
    M5.Lcd.setCursor(100, 110, 4);
    M5.Lcd.printf("B:%d      ", button_data);
  }
  // for (uint8_t channel = 0; channel < TCA9548A_MAX_CHANNELS; channel++) {
  //   M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * channel, FRONT);
  //   M5.Lcd.printf(
  //       "                                                                ");
  //   M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * channel, FRONT);
  //   M5.Lcd.printf("CH%d : ", channel);
  //   returnCode = tca9548a.selectChannel(channel);
  //   if (returnCode == 0) {
  //     for (address = 0x01; address < 0x7F; address++) {
  //       Wire.beginTransmission(address);
  //       returnCode = Wire.endTransmission();
  //       if (returnCode == 0) {
  //         Serial.print("I2C device = ");
  //         M5.Lcd.printf("0X%X  ", address);
  //       }
  //     }
  //   }
  //   delay(200);
  // }
}