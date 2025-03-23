#include "wifi.h"
#include "setts.h"

void setup() {
    Serial.begin(115200);
    Serial.println();

    wifi::begin();
    setts::begin();
}

void loop() {
    setts::tick();

    static long timer = 0;
    long mil = millis();
    if (mil - timer >= 500)
    {
        timer = mil;
        
        setts::sendData(
            random(80, 100),
            random(20, 50),
            random(100)
        );

        setts::waterAlarm(random(2) == 0);
    }
}