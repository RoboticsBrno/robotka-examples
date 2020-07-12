#include "robotka.h"

//speciální typ konsatanty, nejdou do ní ukládat hodnoty. Tato popisuje počet LED na pásku.
#define LED_COUNT 8

//Globálně definovaná proměnná, je dostupná z celého programu
uint8_t hue = 0;

void showGradient() {
    hue += 15;
    for (int i = 0; i != LED_COUNT; i++) {
        //model HSV: první proměnná mění barvu, druhá intenzitu barev a třetí intenzitu svícení.¨
        // Oproti RGB stačí pro změnu barvy měnit pouze jednu hodnotu.
        rkSmartLedsHSV(i, (hue + 30 * i), 255, 255);
    }
}

void showRGB(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < LED_COUNT; i++) {
        //model RGB: první proměnná = intenzita červené, druhá proměnná = intenzita zelené, třetí proměnná = intenzita modré
        rkSmartLedsRGB(i, r, g, b);
    }
}

void setup() {
    rkConfig cfg;
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
