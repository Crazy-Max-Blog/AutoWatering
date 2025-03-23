#include <Arduino.h>

#include "wifi.h"
#include "setts.h"
#include "sensor/sensor.h"

void setup() {
    Serial.begin(115200);
    Serial.println();

    wifi::begin();
    setts::begin();
    sensor::init();
}

void loop() {
    setts::tick();
    sensor::tick();
}