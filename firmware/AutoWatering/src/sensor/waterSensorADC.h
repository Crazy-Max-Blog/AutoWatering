#pragma once

namespace sensor {
    class waterSensorADC : public waterSensorBase {
        public:

        waterSensorADC(byte temp_pin, byte hum_pin) : waterSensorBase() {
            _temp_pin = temp_pin;
            _hum_pin = hum_pin;
            pinMode(32, OUTPUT);
        }

        void init() {
            
        }
        
        byte getWater() {
            return constrain(map(analogRead(34), 3500, 1500, 0, 100), 0, 100);//random(80, 100);
        }

        void water(byte state) {
            Serial.println("waterADC");
            digitalWrite(32, state);
        }

        private:
        byte _temp_pin;
        byte _hum_pin;
    };
}