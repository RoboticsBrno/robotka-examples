#pragma once

#include "robotka.h"

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    rkConfig cfg;
    rkSetup(cfg);

    while (1) {
        rkLedBlue();
        rkLedRed(false);
        delay(300);
        rkLedRed();
        rkLedBlue(false);
        delay(300);
    }
}