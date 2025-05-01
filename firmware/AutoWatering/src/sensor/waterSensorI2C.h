#pragma once

#include <CrazyMgBot.h>

namespace sensor {
    class waterSensorI2C : public waterSensorBase {
        public:

        waterSensorI2C(byte skl_pin, byte sda_pin) : waterSensorBase() {
            _skl_pin = skl_pin;
            _sda_pin = sda_pin;
            pinMode(25, OUTPUT);
        }

        void init() {
            
        }
        
        byte getWater() {
            return random(30, 50);
        }

        void water(byte state) {
            Serial.println("waterI2C");
            digitalWrite(25, state);
        }

        private:
        byte _skl_pin;
        byte _sda_pin;
    };
}