#pragma once

namespace CMB {
    class BaseDev {
        public:
        BaseDev() {}
        BaseDev(byte port) {_port = port;}

        void setPort(byte port) {
            _port = port;
            initPort();
        }

        virtual void initPort() {
            CMB::MGB_I2C63EN::setPort(_port);
        }

        protected:
        byte _port = 0;
    };
}