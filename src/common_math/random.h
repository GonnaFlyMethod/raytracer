#pragma once

#include <random>

namespace CommonMath{
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
}
