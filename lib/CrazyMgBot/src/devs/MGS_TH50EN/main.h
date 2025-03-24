#pragma once

#include "./MCP3221/MCP3221.h"
#include "./Adafruit_MCP9808_Library/Adafruit_MCP9808.h"

namespace CMB {
    class MGS_TH50EN : public CMB::BaseDev {
        public:
        Adafruit_MCP9808 tempsensor;
        MCP3221 humsensor;

        int a = 2380;
        int b = 1165;

        MGS_TH50EN(const byte port = 0, byte addr = 0x4E) : CMB::BaseDev(port), humsensor(addr) {}

        void begin() {
            initPort();
            run = tempsensor.begin(0x18);
        }

        void tick() {
            static long timer = 0;
            long mil = millis();
            if((mil - 100 >= timer) && run) {
                initPort();
                temp = tempsensor.readTempC();
                if(tr_hum) hum = map(humsensor.getData(), a, b, 0, 100);
                else       hum = humsensor.getData();
            }
        }

        int hum = 0;
        float temp = 0;
        
        bool tr_hum = true;

        private:
        bool run = false;
    };
}