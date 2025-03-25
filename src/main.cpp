#include <Arduino.h>

#include "./settings.h"

#include "wific.h"
#include "setts.h"
#include "sensor/sensor.h"
#include "tg.h"
#include "mqtt.h"

void setup() {
    Serial.begin(115200);
    Serial.println();

    wifi::begin();
    setts::begin();
    sensor::init();
    tg::init();
    mqtt::init();
}

void loop() {
    setts::tick();
    sensor::tick();
    tg::tick();
    mqtt::tick();
}