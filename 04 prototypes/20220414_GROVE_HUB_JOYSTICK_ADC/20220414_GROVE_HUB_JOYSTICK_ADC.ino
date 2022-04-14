#include <M5Stack.h>

#define JOY_ADDR 0x52  // define Joystick I2C address.  定义摇杆的I2C地址
#define ADDR_ADC121 0x50  // For v1.0 & v1.1, I2C address is 0x55
#define V_REF 3.00

#define REG_ADDR_RESULT 0x00
#define REG_ADDR_ALERT 0x01
#define REG_ADDR_CONFIG 0x02
#define REG_ADDR_LIMITL 0x03
#define REG_ADDR_LIMITH 0x04
#define REG_ADDR_HYST 0x05
#define REG_ADDR_CONVL 0x06
#define REG_ADDR_CONVH 0x07
unsigned int angleData;
float analogVal = 0;  // convert

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setCursor(70, 0, 4);
  M5.Lcd.println(("Joystick Test"));
  dacWrite(25, 0);  // disable the speak noise.  禁用语音噪音
  Wire.begin(21, 22, 400000UL);
}

char data[100];
void loop() {
  static uint8_t x_data, y_data, button_data;
  Wire.requestFrom(
      JOY_ADDR,
      3);  // Request 3 bytes from the slave device.  向从设备请求3个字节
  delay(1);
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
  Wire.requestFrom(ADDR_ADC121, 2);  // request 2byte from device
  delay(1);
  if (Wire.available() <= 2) {
    angleData = (Wire.read() & 0x0f) << 8;
    angleData |= Wire.read();
    M5.Lcd.setCursor(100, 140, 4);
    M5.Lcd.printf("A:%d      ", angleData);
  }
  Serial.print(x_data);
  Serial.print(",");
  Serial.print(y_data);
  Serial.print(",");
  Serial.print(button_data);
  Serial.print(",");
  Serial.println(angleData);

  delay(10);
}