#pragma once

//#include <CrazyMgBot.h>
#include "../settings.h"
#include "sens.h"

namespace sensor {
    //CMB::MGR_2I2C relay(RELAY_PORT);

    void init_water() {
        //Wire.begin();
        //relay.begin();
        //relay.setPin(0, 0);
        //relay.setPin(1, 0);
    }

    long timer_1 = 0; bool en_1 = 0;
    long timer_2 = 0; bool en_2 = 0;

    void tick_water() {
        long mil = millis();
        if(en_1 && mil - timer_1 >= (int)db::db[kk::water_time_1] * 1000) {
            //relay.setPin(0, 0);
            sens[0]->water(0);
            en_1 = 0;
        }
        
        if(en_2 && mil - timer_2 >= (int)db::db[kk::water_time_2] * 1000) {
            //relay.setPin(1, 0);
            sens[1]->water(0);
            en_2 = 0;
        }
    }

    void water(byte id) {
        if(id == 0) {timer_1 = millis();en_1 = 1;}
        else {timer_2 = millis();en_2 = 1;}
        //relay.setPin(id, 1);
        sens[id]->water(1);
    }

    /*void water(byte id) {
        relay.setPin(id, 1);
        delay((int)db::db[id == 0 ? kk::water_time_1 : kk::water_time_2] * 1000);
        relay.setPin(id, 0);
    }*/
}