#include <M5Stack.h>

#define BITS_PER_PIXEL 1
#define ADDRESS 0x52

TFT_eSprite img = TFT_eSprite(&M5.Lcd);
int x_data;
int y_data;
int button_data;

void drawCircle(int x, int y, int c) {
  img.setColorDepth(BITS_PER_PIXEL);
  img.createSprite(320, 240);
  img.fillCircle(x, y, 10, c);
  img.pushSprite(0, 0);
  img.deleteSprite();
}

void setup(void) {
  M5.begin();
  M5.Power.begin();
  Wire.begin();  // マスターとしてI2C通信を開始
}

void loop() {
  Wire.requestFrom(ADDRESS, 3);
  if (Wire.available()) {
    x_data = Wire.read();
    y_data = Wire.read();
    button_data = Wire.read();
    x_data = map(x_data, 0, 255, 320, 0);
    y_data = map(y_data, 0, 255, 0, 240);
    drawCircle(x_data, y_data, 0x0FFF);
  }
  delay(10);
}