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
    double u = p.x() - std::floor(p.x());
    double v = p.y() - std::floor(p.y());
    double w = p.z() - std::floor(p.z());

    int i = static_cast<int>(floor(p.x()));
    int j = static_cast<int>(floor(p.y()));
    int k = static_cast<int>(floor(p.z()));

    double c[2][2][2];

    for (int di = 0; di < 2;di++){
        for (int dj = 0; dj < 2; dj++){
            for (int dk = 0; dk < 2;dk++){
                c[di][dj][dk] = this->ranfloat[
                    perm_x[(i+di) & 255] ^
                    perm_y[(j+dj) & 255] ^
                    perm_z[(k+dk) & 255]
                ];
            }
        }
    }

    // TODO: return value from trilinear interpolation

    return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

// The linear interpolation can be described in the following general formula:
// B*(t) + A*(1-t), where's A is the starting point of interpolation and B is the end point:

// 10(A)________________________________25(B)

// + in linear interpolation plays the same role in the trilinear one
