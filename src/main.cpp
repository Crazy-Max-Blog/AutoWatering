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
}