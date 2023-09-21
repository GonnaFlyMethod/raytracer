#pragma once

namespace CommonMath{
    inline double clamp(double x, double min, double max){
        // Clamps value in the interval [min, max]

        if (x < min)return min;
        if (x > max) return max;
        return x;
    }
}

