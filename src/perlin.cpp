#include "perlin.h"
#include "common_math.h"


Perlin::Perlin() {
    this->ranfloat = new double[Perlin::point_count];

    for (int i = 0;i < Perlin::point_count;i++){
        ranfloat[i] = random_double();
    }

    this->perm_x = perlin_generate_permutations();
    this->perm_y = perlin_generate_permutations();
    this->perm_z = perlin_generate_permutations();
}

Perlin::~Perlin() {
    delete[] this->ranfloat;
    delete[] this->perm_x;
    delete[] this->perm_y;
    delete[] this->perm_z;
}

int *Perlin::perlin_generate_permutations() {
    int* p = new int[Perlin::point_count];

    for (int i = 0;i < Perlin::point_count;i++){
        p[i] = i;
    }

    for (int i = Perlin::point_count - 1; i > 0;i--){
        int target = random_int(0, i);
        int tmp = p[i];

        p[i] = p[target];
        p[target] = tmp;
    }

    return p;
}

double Perlin::noise(const Point3& p) const{
    int i = static_cast<int>(8 * p.x()) & 255;
    int j = static_cast<int>(8 * p.y()) & 255;
    int k = static_cast<int>(8 * p.z()) & 255;

    return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}
