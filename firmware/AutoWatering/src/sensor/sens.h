#pragma once

#include "waterSensorBase.h"
#include "waterSensorI2C.h"
#include "waterSensorADC.h"

namespace sensor {
    waterSensorBase* sens[] = {new waterSensorADC(WATER_PORT_FIRST), new waterSensorI2C(WATER_PORT_SECOND)};
}