#pragma once

#include "constants.h"

namespace CommonMath{
    inline double degrees_to_radians(double deg){
        return deg * CommonMath::pi / 180;
    }
}