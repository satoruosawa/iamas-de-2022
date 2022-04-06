// PbHub
// seeed studio Grove - Sound Sensor

#include <M5Stack.h>
#include <Wire.h>

#include "porthub.h"

#define X_OFFSET 10
#define Y_OFFSET 18

PortHub porthub;
uint8_t HUB_ADDR[6] = {HUB1_ADDR, HUB2_ADDR, HUB3_ADDR,
                       HUB4_ADDR, HUB5_ADDR, HUB6_ADDR};

void setup() {
  M5.begin(true, false, true);
  Serial.begin(9600);
  M5.Power.begin();
  porthub.begin();
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(4);
}

int x = 0;
void loop() {
  x++;
  if (x > 320) {
    x = 0;
    M5.Lcd.clear(BLACK);
  }
  M5.Lcd.drawLine(x, 0, x, porthub.hub_a_read_value(HUB_ADDR[0]) / 10, WHITE);
  // Serial.println(porthub.hub_a_read_value(HUB_ADDR[0]));
}
