#pragma once

namespace CMB {
    class MGS_TH50 : public CMB::BaseDev {
        public:
        const float air_value    = 1587.0;
        const float water_value  = 800.0;

        const float k = 6.27;

        MGS_TH50(const byte port = 0) : CMB::BaseDev(port) {}

        void initPort() {
            if(!(8 <= _port <= 10)) return;
            _humPin = CMB::MGB_I2C63EN::ports[_port - 3][1];
            _tempPin = CMB::MGB_I2C63EN::ports[_port - 3][0];
            pinMode(_humPin, INPUT);
            pinMode(_tempPin, INPUT);
        }

        void begin() {
            initPort();
            run = true;
        }

        void tick() {
            static long timer = 0;
            long mil = millis();
            if((mil - 100 >= timer) && run) {
                hum = map(analogRead(_humPin), air_value, water_value, 0, 100);
                temp = ((analogRead(_tempPin) / 4095 * k) - 0.5) * 100;
            }
        }

        int hum = 0;
        int temp = 0;

        private:
        bool run = false;
        byte _humPin, _tempPin;
    };
}