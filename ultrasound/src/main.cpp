#include "robotka.h"

// Rozsviti 0-4 LEDky podle toho, jakou vzdalenost nameri ultrazvukovy senzor.
// Kazda rozsvicena LEDka odpovida 10 cm namerene vzdalenosti.
void setLedsByDistance(uint32_t distance) {
    // rozdeleno na useky po 100 mm (10 cm)
    if (distance < 100) {
        rkLedAll(false);
    } else if (distance < 200) {
        rkLedById(1, true);
        rkLedById(2, false);
        rkLedById(3, false);
        rkLedById(4, false);
    } else if (distance < 300) {
        rkLedById(1, true);
        rkLedById(2, true);
        rkLedById(3, false);
        rkLedById(4, false);
    } else if (distance < 400) {
        rkLedById(1, true);
        rkLedById(2, true);
        rkLedById(3, true);
        rkLedById(4, false);
    } else {
        rkLedAll(true);
    }
}

// Pipani pomoci bzucaku podobne jako u senzoru v aute.
void beepLikeCarSensor(uint32_t beepingPeriodMs) {
    static bool isActive = false;
    static uint32_t nextChangeMs = 0;

    if (millis() < nextChangeMs) {
        return;
    } else {
        isActive = (!isActive || (beepingPeriodMs < 100)) && (beepingPeriodMs < 1000);
        rkBuzzerSet(isActive && rkButtonIsPressed(BTN_DOWN));
        nextChangeMs += beepingPeriodMs/4;
    }
}

// Piskani bzucakem, pokud je namerena vzdalenost mensi nez 300 mm.
void beepByDistance(uint32_t distance) {
    if (distance < 300)
        // Pipa pouze kdyz je stisknute tlacitko UP.
        rkBuzzerSet(rkButtonIsPressed(BTN_DOWN));
    else
        rkBuzzerSet(false);
}

// Funkce setup se zavolá vždy po startu robota.
void setup() {
    rkConfig cfg;
    // Upravte nastavení, například:
    // cfg.motor_max_power_pct = 30; // limit výkonu motorů na 30%
    rkSetup(cfg);

    while (true) {
        uint32_t distance = rkUltraMeasure(1);
        printf("%d\n", distance);

        setLedsByDistance(distance);
        //beepByDistance(distance);
        beepLikeCarSensor(distance);
    }
}
