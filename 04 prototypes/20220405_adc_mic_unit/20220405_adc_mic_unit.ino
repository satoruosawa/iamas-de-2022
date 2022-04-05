#include <Wire.h>

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

unsigned int getData;
float analogVal = 0;  // convert

void setup() {
  Serial.begin(9600);
  dacWrite(25, 0);
  Wire.begin();
  Wire.beginTransmission(ADDR_ADC121);  // transmit to device
  Wire.write(REG_ADDR_CONFIG);          // Configuration Register
  Wire.write(0x20);
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(ADDR_ADC121);  // transmit to device
  Wire.write(REG_ADDR_RESULT);          // get result
  Wire.endTransmission();

  Wire.requestFrom(ADDR_ADC121, 2);  // request 2byte from device
  delay(1);
  if (Wire.available() <= 2) {
    getData = (Wire.read() & 0x0f) << 8;
    getData |= Wire.read();
  }
  Serial.println(getData);
}
