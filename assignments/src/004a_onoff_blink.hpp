#pragma once

#include "robotka.h"

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    bool blink = false;

    rkConfig cfg;
    rkSetup(cfg);

    while (1) {
        while (blink) {
            rkLedBlue();
            delay(100);
            rkLedBlue(false);
            delay(100);
            if (rkButtonUp()) {
                blink = false;
                delay(200);
            }
        }
        if (rkButtonUp()) {
            blink = true;
            delay(200);
        }
    }
}