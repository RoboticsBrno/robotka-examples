#pragma once

#include "robotka.h"

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    bool blink = false;

    rkConfig cfg;
    rkSetup(cfg);

    while (1) {
        while(!rkButtonUp()){
        }
        delay(200);
        while (!rkButtonUp()) {
            rkLedBlue();
            delay(100);
            rkLedBlue(false);
            delay(100);
            if (rkButtonUp()) {
                blink = false;
                delay(200);
            }
        }
        delay(200);
    }
}