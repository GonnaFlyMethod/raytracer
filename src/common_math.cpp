#include <random>

#include "common_math.h"

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
    return min+(max-min) * random_double();
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

