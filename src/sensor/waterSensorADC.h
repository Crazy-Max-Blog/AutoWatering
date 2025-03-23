#pragma once

namespace sensor {
    class waterSensorADC : public waterSensorBase {
        public:

        waterSensorADC(byte temp_pin, byte hum_pin) : waterSensorBase() {
            _temp_pin = temp_pin;
            _hum_pin = hum_pin;
        }

        void init() {
            
        }
        
        byte getWater() {
            return random(80, 100);
        }

        void water() {
            Serial.println("waterADC");
        }

        private:
        byte _temp_pin;
        byte _hum_pin;
    };
}