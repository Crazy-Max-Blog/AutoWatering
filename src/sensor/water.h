#pragma once

#include <CrazyMgBot.h>
#include "../settings.h"

namespace sensor {
    CMB::MGR_2I2C relay(RELAY_PORT);

    void init_water() {
        Wire.begin();
        relay.begin();
        relay.setPin(0, 0);
        relay.setPin(1, 0);
    }

    void water(byte id) {
        relay.setPin(id, 1);
        delay((int)db::db[id == 0 ? kk::water_time_1 : kk::water_time_2] * 1000);
        relay.setPin(id, 0);
    }
}