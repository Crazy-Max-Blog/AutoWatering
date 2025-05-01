#pragma once

#include "./PCA9536_modified/PCA9536.h"

namespace CMB {
    class MGR_2I2C : public CMB::BaseDev {
        public:
        Pca9536::PCA9536 pca9536;

        MGR_2I2C(const byte port = 0) : CMB::BaseDev(port) {}

        void begin() {
            initPort();
            pca9536.reset();
            pca9536.setMode(Pca9536::IO_OUTPUT);
        }

        void tick() {}

        void setPin(byte port, bool state) {initPort();pca9536.setState(Pca9536::pin_t(port), Pca9536::state_t(state));}
    };
}