#include "robotka.h"
#include <Arduino.h>

void setup() {
    rkConfig cfg;
    // Upravte nastavení, například:
    cfg.motor_max_power_pct = 30; // limit výkonu motorů na 30%
    rkSetup(cfg);

    // Sem patří váš kód

    rkLedBlue();

    while (true) {
        delay(2000);
        rkLedRed(true);

        // Dopředu na 100%
        rkMotorsSetSpeed(100, 100);
        delay(2000);

        // Otočka na místě doprava
        rkMotorsSetSpeed(100, -100);
        delay(2000);

        // Otočka na místě doleva
        rkMotorsSetSpeed(-100, 100);
        delay(2000);

        // Dozadu
        rkMotorsSetSpeed(-100, -100);
        delay(2000);

        // Zastavit
        rkLedRed(false);
        rkMotorsSetSpeed(0, 0);
        delay(2000);
    }
}
