#pragma once

#include "robotka.h"

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    int speed = 2000;

    rkConfig cfg;
    rkSetup(cfg);

    while (1) {
        rkLedBlue();
        delay(speed / 2);
        rkLedBlue(false);
        delay(speed / 2);
        if (rkButtonUp()) {
            speed /= 2;
            delay(200);
        }
        if (rkButtonDown()) {
            speed *= 2;
            delay(200);
        }
    }
}