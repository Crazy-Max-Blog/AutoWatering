#pragma once

#include "./PCA9634-0.2.1/PCA9634.h"

namespace CMB {
    class MGL_RGB3 : public CMB::BaseDev, public CMB::Base_RGB {
        public:
        PCA9634 leds;

        MGL_RGB3(const byte port = 0, byte addr = 0x1C) : CMB::BaseDev(port), CMB::Base_RGB(), leds(addr) {}

        void begin() {
            run = true;
            initPort();
            leds.begin();
            for (int ch = 0; ch < 8; ch++) 
                leds.setLedDriverMode(ch, PCA9634_LEDPWM);
        }

        void tick() {
            if(color.RGB888 != _color.RGB888) {
                _color = color;
                setRGB(_color);
            }
        }

        void setR(byte val) {if(run) {initPort();leds.write1(3, val);}}
        void setG(byte val) {if(run) {initPort();leds.write1(2, val);}}
        void setB(byte val) {if(run) {initPort();leds.write1(5, val);}}

        private:
        bool run = false;
    };
}