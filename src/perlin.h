#pragma once

#include <memory>
#include "common_math/vec3.h"

// TODO: replace raw pointers on unique_ptr

class Perlin {
private:
    static const int point_count = 256;
    CommonMath::Vec3* random_vec;
    int* perm_x;
    int* perm_y;
    int* perm_z;

    int* perlin_generate_permutations();

public:
    Perlin();
    ~Perlin();
    double turbulence(const CommonMath::Point3& p, int depth=7) const;
    double noise(const CommonMath::Point3& p) const;
    static double trilinear_interpolation(CommonMath::Vec3 c[2][2][2], double u, double v, double w);
};
