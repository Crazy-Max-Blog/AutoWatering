#pragma once

#include "main.h"

namespace CMB {
    class MGB_LED : public CMB::BaseDev {
        public:
        MGB_LED() {}
        MGB_LED(byte port) : CMB::BaseDev(port) {}

        void setVal(bool val) {
            _val = val;
            digitalWrite(CMB::BaseDev::_port, _val);
        }

        private:
        bool _val = false;
    };
}