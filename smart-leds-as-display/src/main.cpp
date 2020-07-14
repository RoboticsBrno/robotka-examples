#include "robotka.h"

#include <array>
#include <vector>
#include <string>
#include <map>

using Letter5x8 = std::array<std::array<uint8_t, 5>, 8>;

inline uint16_t min(uint16_t a, uint16_t b) {
  return a > b ? b : a;
}

class Color {
public:
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  Color() : r(0), g(0), b(0) {}

  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

  Color operator*(uint8_t scalar) {
    return Color(r*scalar, g*scalar, b*scalar);
  }

  Color operator/(uint8_t scalar) {
    return Color(r/scalar, g/scalar, b/scalar);
  }
};

class Font {
public:
  std::map<uint8_t, Letter5x8> letters;

  Font() {
    letters['0'] = {{
      {{0x00, 0xff, 0xff, 0xff, 0x00}},
      {{0xff, 0x00, 0x00, 0x00, 0xff}},
      {{0xff, 0x00, 0x00, 0x00, 0xff}},
      {{0xff, 0x00, 0x00, 0x00, 0xff}},
      {{0xff, 0x00, 0x00, 0x00, 0xff}},
      {{0xff, 0x00, 0x00, 0x00, 0xff}},
      {{0xff, 0x00, 0x00, 0x00, 0xff}},
      {{0x00, 0xff, 0xff, 0xff, 0x00}}
    }};

    letters['1'] = {{
      {{0x00, 0x00, 0xff, 0x00, 0x00}},
      {{0x00, 0xff, 0xff, 0x00, 0x00}},
      {{0xff, 0x00, 0xff, 0x00, 0x00}},
      {{0x00, 0x00, 0xff, 0x00, 0x00}},
      {{0x00, 0x00, 0xff, 0x00, 0x00}},
      {{0x00, 0x00, 0xff, 0x00, 0x00}},
      {{0x00, 0x00, 0xff, 0x00, 0x00}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}}
    }};

    letters['A'] = {{
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}},
      {{0xff, 0xff, 0xff, 0xff, 0xff}}
    }};
  }

  Letter5x8 get(uint8_t ch) {
    return letters[ch];
  }

  static uint16_t height() {
    return 8;
  }

  static uint16_t width() {
    return 5;
  }
};

Font font;

class Canvas {
public:
  uint16_t sizeX = 8;
  uint16_t sizeY = 8;
  std::vector<Color> canvas;

  uint32_t coords(uint16_t x, uint16_t y) {
    return y*sizeX + x;
  }

  static uint32_t coords(uint16_t x, uint16_t y, uint16_t sizeX) {
    return y*sizeX + x;
  }

  Canvas(uint16_t sizeX, uint16_t sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    canvas.resize(sizeX*sizeY);
    canvas.clear();
  }

  void drawImage(Canvas const &img, uint16_t X, uint16_t Y) {
    uint16_t maxX = min(X + img.sizeX, sizeX);
    uint16_t maxY = min(Y + img.sizeY, sizeY);
    for(uint16_t x=X; x<maxX; x++) {
      for(uint16_t y=Y; y<maxY; y++) {
        canvas[coords(x,y)] = img.canvas[img.coords(x-X, y-Y, img.sizeX)];
      }
    }
  }

  void drawImage(Letter5x8 const &img, uint16_t X, uint16_t Y, Color c) {
    uint16_t maxX = min(X + 5, sizeX);
    uint16_t maxY = min(Y + 8, sizeY);
    for(uint16_t x=X; x<maxX; x++) {
      for(uint16_t y=Y; y<maxY; y++) {
        canvas[coords(x,y)] = (c * img[y-Y][x-X])/255;
      }
    }
  }

  void printText(std::string text, Color c, uint16_t X = 0, uint16_t Y = 0) {
    for(int i=0; i<text.size(); i++) {
      drawImage(font.get(text[i]), X + i * (font.width()+1), Y, c);
    }
  }

  Color get(uint16_t x, uint16_t y) {
      return canvas[coords(x, y)];
  }

  void set(uint16_t x, uint16_t y, Color c) {
      canvas[coords(x, y)] = c;
  }
};


//speciální typ konsatanty, nejdou do ní ukládat hodnoty. Tato popisuje počet LED na pásku.
#define LED_COUNT 8
#define DISPLAY_WIDTH 24

void setup() {
    rkConfig cfg;
    rkSetup(cfg);

    uint8_t speed = 16;
    uint8_t brightness = 32;
    uint8_t colorSwitch = 0;
    
    Color textColor(0, 0, 32);
    Canvas canvas(DISPLAY_WIDTH, LED_COUNT);
    //canvas.printText("1010", textColor, 0, 0);

    while(true) {
        if(rkButtonUp(1)) {
            speed += 4;
        }
        if(rkButtonDown(1)) {
            speed -= 4;
        }
        if(rkButtonLeft(1)) {
            brightness -= 16;
        }
        if(rkButtonRight(1)) {
            brightness += 16;
        }
        if(rkButtonOn(1)) {
            colorSwitch = (colorSwitch+1)%3;
        }

        if(colorSwitch == 0)
            textColor = Color(brightness, 0, 0);
        else if(colorSwitch == 1)
            textColor = Color(0, brightness, 0);
        else
            textColor = Color(0, 0, brightness);
        
        canvas.printText("1010", textColor, 0, 0);

        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            for(int y=0; y<LED_COUNT; y++) {
                rkSmartLedsRGB(y, canvas.get(x,y).r, canvas.get(x,y).g, canvas.get(x,y).b);
            }
            delay(speed);
        }
    }
}
