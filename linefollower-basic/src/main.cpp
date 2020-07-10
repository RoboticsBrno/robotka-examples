#include "robotka.h"

void setup() {
    rkConfig cfg;
    // Upravte nastavení, například:
    cfg.motor_max_power_pct = 40; // limit výkonu motorů na 40%
    rkSetup(cfg);

    // Sem patří váš kód

    bool following = false;
    bool previousLeft = false;

    while (true) {
        if (rkButtonDown(true)) { // Tlačítko DOLŮ: Sleduj čáru
            if (following) {
                rkMotorsSetPower(0, 0); // zastavit robota, aby přestal sledovat
                following = false;
            } else {
                following = true;
            }
            delay(500); // prodleva, abyste stihli uhnout rukou
        }

        // l a r jsou hodnoty ze senzorů v rozmezí 0(nejvíce bílá) až 4095 (nejvíce černá)
        const int l = rkIrLeft();
        const int r = rkIrRight();

        printf("L: %d   R: %d\n", l, r);

        // Sledujeme teď čáru?
        if (following) {

            const int threshold = 2300; // Konstanta - hranice, nad kterou se senzor považuje "nad čárou"

            if (l > threshold) { // čára je pod levým senzorem, doprava!
                rkMotorsSetPower(100, 40);
                previousLeft = false;
            } else if (r > threshold) { // pod pravým senzorem, doleva!
                rkMotorsSetPower(40, 100);
                previousLeft = true;
            } else {
                // Čára není ani pod jedním senzorem. Pokračujme v otáčení ve stejném směru jako dotěď
                // (uloženo v previousLeft), ale ještě ostřeji.
                if (previousLeft) {
                    rkMotorsSetPower(0, 100);
                } else {
                    rkMotorsSetPower(100, 0);
                }
            }
        }
    }
}
