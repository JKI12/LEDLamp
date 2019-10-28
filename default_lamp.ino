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

void showSkyGradient() {
  int sky_gradient[6][3] = {
    {255, 235, 0},
    {255, 100, 0},
    {255, 100, 0},
    {255, 0, 165},
    {255, 0, 165},
    {110, 0, 255}
  };

  float scale_factor = 0.333;

  for (int i = 0; i < 6; i++) {
    for (int j = i * 4; j < ((i + 1) * 4) + 4; j++) {
      pixels.setPixelColor(j, interpolateColour(sky_gradient[i], sky_gradient[i + 1], scale_factor * (i / 4)));
    }
  }

  pixels.show();
}

void showFire() {
  int fire_gradient[2][3] = {
    {128, 9, 9},
    {242, 125, 12},
  };

  int steps = 20;
  float scale_factor = 0.052631579;

  for (int j = 0; j < 2; j++) {
    delay(500);

    for (int i = 0; i < steps; i++) {
      int second_index = 1;

      if (j == 1) {
        second_index = 0;
      }

      uint32_t color = interpolateColour(fire_gradient[j], fire_gradient[second_index], scale_factor * i);

      for (int p = 0; p < NUMPIXELS; p++) {
        pixels.setPixelColor(p, color);
      }

      pixels.show();
      delay(60);
    }
  }
}

void randomColours() {
  int r = random(40, 126);
  int g = random(32);
  int b = random(50, 134);

  for (int p = 0; p < 4; p++) {
    for (int i = 0; i < 6; i++) {
      pixels.setPixelColor(i * 4 + p, pixels.Color(g, r, b));
    }

    pixels.show();
    delay(100);
  }

  delay(5000);

  for (int p = 0; p < 4; p++) {
    for (int i = 0; i < 6; i++) {
      pixels.setPixelColor(i * 4 + p, pixels.Color(0, 0, 0));
    }

    pixels.show();
    delay(100);
  }
}

void clearPixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void ring() {
  int starting_index = random(3, 5);
  int colors[3][3] = {
    {229, 32, 32},
    {17, 193, 29},
    {17, 140, 193}
  };

  int color = random(0, 2);
  
  for (int j = starting_index; j < NUMPIXELS; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      clearPixels();

      for (int k = 0; k < j; k++) {
        int index = i - k;
        pixels.setPixelColor(index, pixels.Color(colors[color][1], colors[color][0], colors[color][2]));
      }

      pixels.show();
      delay(50);
    }

    if (j == (NUMPIXELS - 1)) {
      break;
    }

    for (int i = (NUMPIXELS - j); i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(25);
    }
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(colors[color][1], colors[color][0], colors[color][2]));
  }

  pixels.show();
  delay(5000);
}

void colorFade() {
  int r = random(255);
  int g = random(255);
  int b = random(255);

  float scale_factor = 0.111111;

  int gradient[2][3] = {
    {r, g, b},
    {0, 0, 0},
  };

  for (int i = 0; i < 10; i++) {
    uint32_t color = interpolateColour(gradient[0], gradient[1], scale_factor * i);
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, color);
    }

    pixels.show();
    delay(100);
  }

  delay(250);
}

int scenario = 0;

void setup() {
  pixels.setBrightness(128);

  randomSeed(analogRead(0));
  scenario = random(1, 6);

  pixels.begin();
  pixels.show();
}

void loop() {
  //  GRB
  switch(scenario) {
    case 1:
      showSkyGradient();
      break;
    case 2:
      showFire();
      break;
    case 3:
      randomColours();
      break;
    case 4:
      ring();
      break;
    case 5:
      colorFade();
      break;
  }
}

