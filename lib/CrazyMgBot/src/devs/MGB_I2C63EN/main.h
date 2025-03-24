#pragma once

namespace CMB {
    namespace MGB_I2C63EN {
        /*
          I2C порт 0x07 - выводы GP16 (SDA), GP17 (SCL)
          I2C порт 0x06 - выводы GP4 (SDA), GP13 (SCL)
          I2C порт 0x05 - выводы GP14 (SDA), GP15 (SCL)
          I2C порт 0x04 - выводы GP5 (SDA), GP23 (SCL)
          I2C порт 0x03 - выводы GP18 (SDA), GP19 (SCL)
        */

        byte ports[8][3] = {
            {17, 16},
            {13,  4},
            {15, 14},
            {23,  5},
            {18, 19},
            {26, 25},
            {33, 32},
            {35, 34}
        };

        bool setPort(uint8_t i2c_channel)
        {
            if (i2c_channel >= 0x08) return false;

            Wire.beginTransmission(0x70);
#if !defined(PW548)
            Wire.write(i2c_channel | 0x08); // для микросхемы PCA9547
#else
        	Wire.write(0x01 << i2c_channel); // Для микросхемы PW548A
#endif
            Wire.endTransmission();
            return true; 
        }
    }
}