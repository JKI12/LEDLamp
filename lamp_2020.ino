#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

uint32_t interpolateColour(int color1[], int color2[], float scale_factor) {
  return pixels.Color(
     color1[1] + (color2[1] - color1[1]) * scale_factor,
     color1[0] + (color2[0] - color1[0]) * scale_factor,
     color1[2] + (color2[2] - color1[2]) * scale_factor
   );
}

void clearPixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void setRingColour(uint32_t color) {
  for (int p = 0; p < NUMPIXELS; p++) {
    pixels.setPixelColor(p, color);
  }
}

void fadeBetweenArray(int gradient[][3], int arraySize) {
  float scaleFactor = 0.052631579;
  int noSteps = 20;

  for (int i = 0; i < arraySize; i++) {
    delay(750);

    for (int j = 0; j < noSteps; j++){
      int nextIndex = i + 1;

      if (nextIndex == arraySize) {
        nextIndex = 0;
      }

      uint32_t color = interpolateColour(gradient[i], gradient[nextIndex], scaleFactor * j);

      setRingColour(color);

      pixels.show();
      delay(80);
    }
  }
}

void showSpring() {
  int springGradient[3][3] = {
    { 205, 37, 63 },
    { 213, 54, 110 },
    { 202, 76, 87 }
  };

  fadeBetweenArray(springGradient, 3);
}

void showSummer() {
  int summerGradient[4][3] = {
    { 0, 223, 255 },
    { 0, 255, 171 },
    { 244, 112, 100 },
    { 255, 221, 18 }
  };

  fadeBetweenArray(summerGradient, 4);
}

void showAutumn() {
  int autumnGradient[4][3] = {
    { 183, 73, 10 },
    { 238, 102, 64 },
    { 117, 28, 14 },
    { 189, 138, 11 }
  };

  fadeBetweenArray(autumnGradient, 4);
}

void showWinter() {
  int winterGradient[5][3] = {
    { 181, 229, 231 },
    { 113, 195, 219 },
    { 28, 179, 210 },
    { 6, 122, 159 },
    { 33, 59, 84 }
  };

  fadeBetweenArray(winterGradient, 5);
}

void loadingCircle() {
  int colour = pixels.Color(255, 100, 10);
  int space = 6;

  for (int p = 0; p < (NUMPIXELS / space); p++) {
    clearPixels();

    for (int i = 0; i < space; i++) {
      pixels.setPixelColor(i * 4 + p, colour);
    }
      pixels.show();
      delay(100);
  }
}

void crazyCircle() {
  float scaleFactor = 0.11111;

  int gradient[2][3] = {
    { random(15, 24), random(40, 178), random(40, 100) },
    { random(40, 60), random(40, 60), random(40, 50) }
  };

  for (int i = 0; i < NUMPIXELS; i++) {
    uint32_t color = interpolateColour(gradient[0], gradient[1], scaleFactor * i);
    pixels.setPixelColor(i, color);
  }
  pixels.show();
  delay(10000);
}

int scenario = 0;

void setup() {
  pixels.setBrightness(80);

  randomSeed(analogRead(0));
  scenario = random(1, 6);

  pixels.begin();
  pixels.show();
}

void loop() {
  switch(scenario) {
    case 1:
      showSpring();
      break;
    case 2:
      showSummer();
      break;
    case 3:
      showAutumn();
      break;
    case 4:
      showWinter();
      break;
    case 5:
      loadingCircle();
      break;
    case 6:
      crazyCircle();
      break;
  }
}
