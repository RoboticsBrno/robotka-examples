#include "robotka.h"

void setLedsByDistance(uint32_t distance) {
    // rozdeleno na useky po 100 mm (10 cm)
    if(distance < 100) {
        rkLedAll(false);
    } else if(distance < 200) {
        rkLedById(1, true);
        rkLedById(2, false);
        rkLedById(3, false);
        rkLedById(4, false);
    } else if(distance < 300) {
        rkLedById(1, true);
        rkLedById(2, true);
        rkLedById(3, false);
        rkLedById(4, false);
    } else if(distance < 400) {
        rkLedById(1, true);
        rkLedById(2, true);
        rkLedById(3, true);
        rkLedById(4, false);
    } else {
        rkLedAll(true);
    }
}

void updateBeeping(uint32_t beepingPeriodMs) {
    static bool isActive = false;
    static uint32_t nextChangeMs = 0;

    if(millis() < nextChangeMs) {
        return;
    } else {
        isActive = !isActive || (beepingPeriodMs < 100);
        rkBuzzerSet(isActive);
        nextChangeMs += beepingPeriodMs;
    }
}

void beepByDistance(uint32_t distance) {
    if(distance < 300)
        rkBuzzerSet(true);
    else
        rkBuzzerSet(false);
    //updateBeeping( (distance - distance % 100) );
}

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    rkConfig cfg;
    // Upravte nastavení, například:
    // cfg.motor_max_power_pct = 30; // limit výkonu motorů na 30%
    rkSetup(cfg);

    uint32_t distance = 10000; // max 10 m
    for(int id=1; id<=4; id++) {
        distance = max(distance, rkUltraMeasure(id));
    }

    setLedsByDistance(distance);
    beepByDistance(distance);
}
