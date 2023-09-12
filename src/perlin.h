#pragma once

#include <memory>
#include "vec3.h"

// TODO: replace raw pointers on unique_ptr

class Perlin {
private:
    static const int point_count = 256;
    double* ranfloat;
    int* perm_x;
    int* perm_y;
    int* perm_z;

    int* perlin_generate_permutations();

public:
    Perlin();
    ~Perlin();
    double noise(const Point3& p) const;
    static double trilinear_interpolation(double c[2][2][2], double u, double v, double w);
};
