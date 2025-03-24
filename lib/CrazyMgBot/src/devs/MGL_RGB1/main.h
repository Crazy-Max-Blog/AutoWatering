#pragma once

#include "./TLC59108_modified/TLC59108.h"

namespace CMB {
    class MGL_RGB1 : public CMB::BaseDev, public CMB::Base_RGB {
        public:
        TLC59108 leds;

        #define I2C_ADDR_BASE TLC59108::I2C_ADDR::BASE
        MGL_RGB1() : CMB::BaseDev(), CMB::Base_RGB(), leds(I2C_ADDR_BASE + 7) {}
        MGL_RGB1(byte port, byte addr = 7) : CMB::BaseDev(port), CMB::Base_RGB(), leds(I2C_ADDR_BASE + addr) {}

        void begin() {
            run = true;
            initPort();
            leds.init();
            leds.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
        }

        void setR(byte val) {if(run) {initPort();leds.setBrightness(3, val);}}
        void setG(byte val) {if(run) {initPort();leds.setBrightness(2, val);}}
        void setB(byte val) {if(run) {initPort();leds.setBrightness(5, val);}}

        private:
        bool run = false;
    };
}    