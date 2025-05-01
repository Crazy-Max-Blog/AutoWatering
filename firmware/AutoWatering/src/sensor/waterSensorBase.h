#pragma once

namespace sensor {
    class waterSensorBase {
        public:
        virtual void init() = 0;

        virtual byte getWater() = 0;

        virtual void water(byte state) = 0;
    };
}