#include "robotka.h"

#define LED_COUNT 8

void showGradient() {
    static uint8_t hue;
    hue++;
    for (int i = 0; i != LED_COUNT; i++) {
        rkSmartLedsHSV(i, (hue + 30 * i), 255, 255);
    }
}

void showRGB(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < LED_COUNT; i++) {
        rkSmartLedsRGB(i, r, g, b);
    }
}

void setup() {
    rkConfig cfg;
    cfg.smart_leds_count = LED_COUNT; //výchozí hodnota je 8
    rkSetup(cfg);

    while (true) {
        if (millis() % 10000 < 5000) {
            //Duha!
            showGradient();
        } else {
            //Nastavení bílé barvy na všechny led
            showRGB(255, 255, 255);
        }

        delay(50);
    }
}
