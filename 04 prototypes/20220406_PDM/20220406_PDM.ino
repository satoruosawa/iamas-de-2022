#include <driver/i2s.h>

#define I2S_NUM I2S_NUM_0  // 0 or 1
#define I2S_SAMPLE_RATE 16000
#define I2S_BUFFER_SIZE 512
#define I2S_PIN_CLK I2S_PIN_NO_CHANGE
#define I2S_PIN_WS 22
#define I2S_PIN_DOUT I2S_PIN_NO_CHANGE
#define I2S_PIN_DIN 21

int16_t i2s_sambles[I2S_BUFFER_SIZE];
void i2sMicInit() {
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
      .sample_rate = I2S_SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ALL_LEFT,
      .communication_format = I2S_COMM_FORMAT_I2S,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0};
  i2s_pin_config_t pin_config = {
      .bck_io_num = I2S_PIN_CLK,
      .ws_io_num = I2S_PIN_WS,
      .data_out_num = I2S_PIN_DOUT,
      .data_in_num = I2S_PIN_DIN,
  };
  i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM, &pin_config);
}
void setup() {
  Serial.begin(115200);
  delay(1000);

  i2sMicInit();
}

void loop() {
  size_t bytes_read;
  i2s_read(I2S_NUM, (void *)i2s_sambles, sizeof(i2s_sambles), &bytes_read,
           portMAX_DELAY);

  // Display only the first data
  Serial.printf("%6d\n", i2s_sambles[0]);
}