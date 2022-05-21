#include <M5Stack.h>

#include "UNIT_ENV.h"

SHT3X sht30;
QMP6988 qmp6988;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

void setup() {
  M5.begin();             // Init M5Stack.  初始化M5Stack
  M5.Power.begin();       // Init power  初始化电源模块
  M5.lcd.setTextSize(2);  // Set the text size to 2.  设置文字大小为2
  Wire.begin();  // Wire init, adding the I2C bus.  Wire初始化, 加入i2c总线
  qmp6988.init();
  M5.lcd.println(F("ENV Unit III test"));
}

void loop() {
  pressure = qmp6988.calcPressure();
  if (sht30.get() == 0) {  // Obtain the data of shT30.  获取sht30的数据
    tmp = sht30.cTemp;     // Store the temperature obtained from shT30.
                           // 将sht30获取到的温度存储
    hum = sht30.humidity;  // Store the humidity obtained from the SHT30.
                           // 将sht30获取到的湿度存储
  } else {
    tmp = 0, hum = 0;
  }
  M5.lcd.fillRect(0, 20, 100, 60,
                  BLACK);  // Fill the screen with black (to clear the screen).
                           // 将屏幕填充黑色(用来清屏)
  M5.lcd.setCursor(0, 20);
  M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n", tmp,
                hum, pressure);
  delay(2000);
}