#pragma once

#include "robotka.h"

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    rkConfig cfg;
    rkSetup(cfg);

    while (1) {
        rkLedBlue();
        delay(50);
        rkLedBlue(false);
        delay(950);
    }
}