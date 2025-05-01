#include <Arduino.h>

#include "./settings.h"

#include "wific.h"
#include "setts.h"
#include "sensor/sensor.h"
#include "tg.h"
#include "mqtt.h"
#include <ArduinoOTA.h>

void setup() {
    Serial.begin(115200);
    Serial.println();

    wifi::begin();
    setts::begin();
    sensor::init();
    tg::init();
    mqtt::init();
    ArduinoOTA.begin();
}

void loop() {
    //Serial.println(1);
    setts::tick();
    //Serial.println(2);
    sensor::tick();
    //Serial.println(3);
    tg::tick();
    //Serial.println(4);
    mqtt::tick();
    ArduinoOTA.handle();
}