#include <M5Stack.h>

int value = 500;

#define motor_pin 21
int freq = 10000;
int ledChannel = 0;
int resolution = 10;
void setup() {
  M5.begin();             // Init M5Stack.  初始化M5Stack
  M5.Power.begin();       // Init power  初始化电源模块
  M5.lcd.setTextSize(2);  // Set the text size to 2.  设置文字大小为2
  M5.Lcd.setCursor(
      110, 10);  // Set the cursor at (110, 10).  将光标设置在(110, 10)处
  M5.Lcd.println("Vibrator");
  ledcSetup(
      ledChannel, freq,
      resolution);  // Sets the frequency and number of counts corresponding to
                    // the channel.  设置通道对应的频率和计数位数
  ledcAttachPin(
      motor_pin,
      ledChannel);  // Binds the specified channel to the specified I/O port for
                    // output.  将指定通道绑定到指定 IO 口上以实现输出
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(50, 120);
  M5.Lcd.printf("%3d", value);
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    value -= 50;
    M5.Lcd.setCursor(50, 120);
    M5.Lcd.printf("%3d", value);
  }
  if (M5.BtnB.wasPressed()) {
    value += 50;
    M5.Lcd.setCursor(50, 120);
    M5.Lcd.printf("%3d", value);
  }
  if (M5.BtnC.wasPressed()) {
    ledcWrite(ledChannel, value);
    delay(400);
    ledcWrite(ledChannel, 0);
  }
}