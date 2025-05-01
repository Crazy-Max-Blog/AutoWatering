#pragma once

#include "./Adafruit_BME280_Library/Adafruit_BME280.h"

namespace CMB {
    class MGS_THP80 : public CMB::BaseDev {
        public:
        Adafruit_BME280 bme280;

        MGS_THP80(const byte port = 0) : CMB::BaseDev(port) {}

        void begin() {
            initPort();
            run = bme280.begin();
            if(!run) run = bme280.begin(0x76);
        }

        void tick() {
            static long timer = 0;
            long mil = millis();
            if((mil - 100 >= timer) && run) {
                initPort();
                t = bme280.readTemperature();
                h = bme280.readHumidity();
                p = bme280.readPressure() / 133.3F;
            }
        }

        float t = 0;
        float h = 0;
        float p = 0;

        private:
        bool run = false;
    };
}