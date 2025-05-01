#pragma once

#include "./SparkFun_SGP30_Arduino_Library-1.0.5/src/SparkFun_SGP30_Arduino_Library.h"

namespace CMB {
    class MGS_CO30 : public CMB::BaseDev {
        public:
        SGP30 sens;

        MGS_CO30(const byte port = 0) : CMB::BaseDev(port) {}

        void begin() {
            initPort();
            run = sens.begin();
            if(run) sens.initAirQuality();
        }

        void tick() {
            static long timer = 0;
            long mil = millis();
            if((mil - 100 >= timer) && run) {
                timer = mil;
                initPort();
                sens.measureAirQuality();
                CO2 = sens.CO2;
                TVOC = sens.TVOC;
            }
        }

        int CO2 = 0;
        int TVOC = 0;

        private:
        bool run = false;
    };
}