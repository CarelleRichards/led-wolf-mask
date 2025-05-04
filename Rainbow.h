class Rainbow {
  public:
  Rainbow() {};
    bool runPattern();

  private:
    const static uint16_t speed = 14;
    uint16_t rainbowShift = (random8(0, 5) * 32) + speed;
    uint16_t rainbowTime = 0;
    const static uint8_t rainbowXfactor = 5;
    const static uint8_t rainbowYfactor = 5;
};

bool Rainbow::runPattern() {
  if (checkButton()) {
    return false;
  }

  for (int16_t x = 0; x < NUM_COLS; x++) {
    for (int16_t y = 0; y < NUM_ROWS; y++) {
      int16_t r = sin16(rainbowTime) / 256;

      int16_t h = sin16(x * r * rainbowXfactor + rainbowTime) + 
                  cos16(y * (-r) * rainbowYfactor + rainbowTime) + 
                  sin16(y * x * (cos16(-rainbowTime) / 256) / 2);

      leds[XY(x, y)] = CHSV((uint8_t)((h / 256) + 128), 255, 255);
    }
  }

  uint16_t oldRainbowTime = rainbowTime;
  rainbowTime += rainbowShift;

  if (oldRainbowTime > rainbowTime) {
    rainbowShift = (random8(0, 5) * 32) + speed;
  }

  setEyeColour(CRGB::White);

  show();

  return true;
}