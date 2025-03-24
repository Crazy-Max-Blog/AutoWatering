#pragma once

#include "./BH1750/src/BH1750.h"

namespace CMB {
    class MGS_L75 : public CMB::BaseDev {
        public:
        BH1750 s; 

        MGS_L75(const byte port = 0, byte addr = 0x4E) : CMB::BaseDev(port) {}

        void begin() {
            initPort();
            run = s.begin();
        }

        void tick() {
            static long timer = 0;
            long mil = millis();
            if((mil - 100 >= timer) && run) {
                initPort();
                lux = s.readLightLevel();
            }
        }

        int lux = 0;

        private:
        bool run = false;
    };
}