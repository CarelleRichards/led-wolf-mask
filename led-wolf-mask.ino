#include <FastLED.h>
#include <JC_Button.h> 

#define DATA_PIN 2
#define NUM_ROWS 11
#define NUM_COLS 9
#define LAST_VISIBLE_LED 56
#define MAX_DIMENSION ((NUM_COLS > NUM_ROWS) ? NUM_COLS : NUM_ROWS)
#define NUM_LEDS (NUM_COLS * NUM_ROWS)
#define PATTERN_MODES 3
#define BRIGHT_MODES 3

int currentMode = 1;
Button modeButton(7);

int currentBrightness = 3;
Button brightnessButton(3);

CRGBArray<NUM_LEDS> leds;

int rightEar[6] = { 18, 19, 20, 21, 22, 23 };
int rightFace[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 11 };
int rightEye[3] = { 8, 9, 10 };
int midline[8] = { 31, 30, 29, 28, 27, 26, 25, 24 };
int leftEye[3] = { 47, 46, 45 };
int leftFace[18] = { 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38 };
int leftEar[6] = { 37, 36, 35, 34, 33, 32 };

// Numbers > LAST_VISIBLE_LED won't light up.
const uint8_t XYTable[] = { 
  56,   32,   57,   58,   59,   60,   61,   23,   62,
  63,   33,   34,   64,   65,   66,   21,   22,   67,
  68,   37,   36,   35,   69,   20,   19,   18,   70,
  44,   38,   39,   40,   31,   15,   16,   17,   11,
  71,   43,   42,   41,   30,   14,   13,   12,   72,
  55,   73,   74,   75,   29,   76,   77,   78,   0,
  54,   45,   79,   80,   28,   81,   82,   10,   1,
  53,   46,   83,   84,   27,   85,   86,   9,    2,
  52,   47,   87,   88,   26,   89,   90,   8,    3,
  51,   48,   91,   92,   25,   93,   94,   7,    4,
  50,   49,   95,   96,   24,   97,   98 ,  6,    5,
};

//        32,                                 23,		
//        33,   34,                     21,   22,		
//        37,   36,   35,         20,   19,   18,
//
//  44,   38,   39,   40,   31,   15,   16,   17,   11,
//        43,   42,   41,   30,   14,   13,   12,
//
//  55,                     29,                     0,
//  54,   45,               28,               10,   1,
//  53,   46,               27,               9,    2,
//  52,   47,               26,               8,    3,
//  51,   48,               25,               7,    4,
//  50,   49,               24,               6,    5,

void setup() { 
  // For logging.
  Serial.begin(57600);

  FastLED.addLeds<WS2812B,  DATA_PIN, GRB>(leds, NUM_LEDS);

  modeButton.begin();
  brightnessButton.begin();
}

void loop() { 
  switch (currentMode) {
    case 1:
      runRainbow();
      break;
    case 2:
      runGradient();
      break;
    case 3:
      runSnake();
      break;
    default:
      currentMode = 1;
      break;
  }
}

// Matrix.
uint16_t XY(uint8_t x, uint8_t y) {
  if ((x >= NUM_COLS) || (y >= NUM_ROWS)) {
    return (LAST_VISIBLE_LED + 1);
  }

  uint8_t i = (y * NUM_COLS) + x;
  uint8_t j = XYTable[i];
  return j;
}

#include "Rainbow.h"
#include "Gradient.h"
#include "Snake.h"

bool checkButton() {
  brightnessButton.read();

  if (brightnessButton.wasReleased()) {
    currentBrightness = currentBrightness < BRIGHT_MODES 
      ? currentBrightness + 1
      : 1;
  }

  modeButton.read();

  if (modeButton.wasReleased()) {
    currentMode = currentMode > PATTERN_MODES 
      ? 1
      : currentMode + 1;
    return true;
  }
  return false;
}

void runRainbow() {
  bool isRunning = true;
  Rainbow rainbow = Rainbow();
  while(isRunning) isRunning = rainbow.runPattern();
}

void runGradient() {
  bool isRunning = true;
  Gradient gradient = Gradient();
  while(isRunning) isRunning = gradient.runPattern();
}

void runSnake() {
  bool isRunning = true;
  Snake snake = Snake();
  while(isRunning) isRunning = snake.runPattern();
}

void setEyeColour(CRGB colour) {
  for (size_t i = 0; i < sizeof(rightEye) / sizeof(rightEye[0]); i++) {
    int num = rightEye[i];
    leds[num] = colour;
  }

  for (size_t i = 0; i < sizeof(leftEye) / sizeof(leftEye[0]); i++) {
    int num = leftEye[i];
    leds[num] = colour;
  }
}

void show() {
  FastLED.show(map(currentBrightness, 1, BRIGHT_MODES, 30, 255));
}