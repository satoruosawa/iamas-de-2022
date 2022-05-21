#include <M5Stack.h>

#include "UNIT_ENV.h"

#define JOY_ADDR 0x52  // define Joystick I2C address.  定义摇杆的I2C地址
SHT3X sht30;
QMP6988 qmp6988;
float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.println(("Joystick Test"));
  dacWrite(25, 0);  // disable the speak noise.  禁用语音噪音
  Wire.begin(21, 22, 400000UL);
  qmp6988.init();
}

char data[100];
void loop() {
  static uint8_t x_data, y_data, button_data;
  Wire.requestFrom(
      JOY_ADDR,
      3);  // Request 3 bytes from the slave device.  向从设备请求3个字节
  if (Wire.available()) {  // If data is received.  如果接收到数据
    x_data = Wire.read();
    y_data = Wire.read();
    button_data = Wire.read();

    M5.Lcd.setCursor(100, 50, 4);
    M5.Lcd.printf("X:%d      ", x_data);
    M5.Lcd.setCursor(100, 80, 4);
    M5.Lcd.printf("Y:%d      ", y_data);
    M5.Lcd.setCursor(100, 110, 4);
    M5.Lcd.printf("B:%d      ", button_data);
  }

  pressure = qmp6988.calcPressure();
  if (sht30.get() == 0) {  // Obtain the data of shT30.  获取sht30的数据
    tmp = sht30.cTemp;     // Store the temperature obtained from shT30.
                           // 将sht30获取到的温度存储
    hum = sht30.humidity;  // Store the humidity obtained from the SHT30.
                           // 将sht30获取到的湿度存储
  } else {
    tmp = 0, hum = 0;
  }
  M5.Lcd.setCursor(100, 140, 4);
  M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n", tmp,
                hum, pressure);

  sprintf(data, "x:%d y:%d button:%d tmp:%f hum:%f\n", x_data, y_data,
          button_data, tmp, hum);
  // sprintf(data, "pressure:%d\n", pressure);
  Serial.print(data);
  delay(200);
}