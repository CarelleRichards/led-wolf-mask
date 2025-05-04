class Gradient {
  public:
    Gradient() {};
    bool runPattern();

  private:
    uint8_t paletteIndex = 0;
    uint8_t paletteNumber = 0;

    const CRGBPalette16 sunset = {
      0xE42065,
      0xE42065,
      0xE42065,
      0xE42065,

      0xF53D58,
      0xF53D58,
      0xF53D58,
      0xF53D58,

      0xFF4B2B,
      0xFFF4B2B,
      0xFF4B2B,
      0xFF4B2B,

      0xF55C1A,
      0xF55C1A,
      0xF55C1A,
      0xF55C1A
    };

    const CRGBPalette16 iceBlue = {
      0x595cff,
      0x595cff,
      0x90AAFF,
      0x90AAFF,

      0x557DFF,
      0x557DFF,
      0x595cff,
      0x595cff,

      0x595cff,
      0x595cff,
      0x557DFF,
      0x90AAFF,

      0x90AAFF,
      0x90AAFF,
      0x595cff,
      0x595cff,
    };

    CRGBPalette16 currentPalette = sunset;
    CRGBPalette16 targetPalette = iceBlue;
};

bool Gradient::runPattern() {
  if (checkButton()) {
    return false;
  }

  fill_palette(leds, NUM_LEDS, paletteIndex, 8, currentPalette, 255, LINEARBLEND);

  EVERY_N_MILLISECONDS(10) {
    paletteIndex++;
  }

  nblendPaletteTowardPalette(currentPalette, targetPalette, 6);

  switch (paletteNumber) {
    case 0:
      targetPalette = sunset;
      break;
    case 1:
      targetPalette = iceBlue;
      break;
  }

  EVERY_N_SECONDS(15) {
    paletteNumber++;

    if (paletteNumber > 1) {
      paletteNumber = 0;
    }
  }

  show();

  return true;
}