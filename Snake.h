class Snake {
  public:
    Snake() {};
    bool runPattern();

  private:
    uint8_t hue;
    const static uint8_t fade = 30;
    const static uint8_t delay = 90;
    
    bool lightLeds(int* leds, int size);
};

bool Snake::runPattern() {
  if (!lightLeds(rightFace, sizeof(rightFace) / sizeof(rightFace[0]))) return false;
  if (!lightLeds(rightEar, sizeof(rightEar) / sizeof(rightEar[0]))) return false;
  if (!lightLeds(midline, sizeof(midline) / sizeof(midline[0]))) return false;
  if (!lightLeds(leftFace, sizeof(leftFace) / sizeof(leftFace[0]))) return false;
  if (!lightLeds(leftEar, sizeof(leftEar) / sizeof(leftEar[0]))) return false;
  return true; 
}

bool Snake::lightLeds(int* ledsArray, int size) {
  for (int i = 0; i < size; i++) {
    leds.fadeToBlackBy(fade);
    int num = ledsArray[i];
    leds[num] = CHSV(hue++, 255, 255);
    show();

    unsigned long start = millis();
    while (millis() - start < delay) {
      if (checkButton()) {
        return false;
      }
    }
  }
  return true;
}