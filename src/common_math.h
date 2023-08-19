#pragma once

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double deg);
inline double random_double();
inline double random_double(double min, double max);
inline double clamp(double x, double min, double max);

#include "ray.h"
#include "vec3.h"