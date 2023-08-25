#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double deg){
    return deg * pi / 180;
};

inline double random_double(){
    // Returns a double real in [0,1).

    static std::uniform_real_distribution<double> distribution(0.0f,1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max){
    // Returns random double in [min, max)

    return min+(max-min) * random_double();
}

inline int random_int(int min, int max){
    // Returns random integer in [min, max]

    return static_cast<int>(random_double(min, max+1));
}

inline double clamp(double x, double min, double max){
    if (x < min){
        return min;
    }

    if (x > max){
        return max;
    }

    return x;
}
