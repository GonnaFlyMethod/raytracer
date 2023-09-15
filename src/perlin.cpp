#include "perlin.h"
#include "common_math.h"


Perlin::Perlin() {
    this->random_vec = new Vec3[Perlin::point_count];

    for (int i = 0;i < Perlin::point_count;i++){
        random_vec[i] = unit_vector(Vec3::random(-1, 1));
    }

    this->perm_x = perlin_generate_permutations();
    this->perm_y = perlin_generate_permutations();
    this->perm_z = perlin_generate_permutations();
}

Perlin::~Perlin() {
    delete[] this->random_vec;
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

    // Makes low contribution even lower and high contribution higher
    u *= u * (3-2*u);
    v *= v * (3-2*v);
    w *= w * (3-2*w);

    int i = static_cast<int>(floor(p.x()));
    int j = static_cast<int>(floor(p.y()));
    int k = static_cast<int>(floor(p.z()));

    Vec3 c[2][2][2];

    for (int di = 0; di < 2;di++){
        for (int dj = 0; dj < 2; dj++){
            for (int dk = 0; dk < 2;dk++){
                c[di][dj][dk] = this->random_vec[
                    perm_x[(i+di) & 255] ^
                    perm_y[(j+dj) & 255] ^
                    perm_z[(k+dk) & 255]
                ];
            }
        }
    }

    return trilinear_interpolation(c, u, v, w);;
}

// See the article
// https://medium.com/@alex.husakou/trilinear-interpolation-for-perlin-noise-samples-raytracing-next-week-df1c6dabe597
// To understand how the trilinear interpolation works

// Find out: Is pixel a discrete point or a quad with X[0;1] and Y[0;1]

double Perlin::trilinear_interpolation(Vec3 c[2][2][2], double u, double v, double w) {
    double accum = 0.0;

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for(int k = 0;k < 2; k++){
                Vec3 weight(u-i, v-j, w-k);

                accum += (u * i + (1 - i) * (1 - u)) *
                         (v * j + (1 - j) * (1 - v)) *
                         (w * k + (1 - k) * (1 - w)) * dot(weight, c[i][j][k]);
            }
        }
    }

    return accum;
}


double Perlin::turbulence(const Point3 &p, int depth) const {
    double accum = 0.0f;
    Point3 temp_p = p;
    double weight = 1.0f;

    for (int i = 0; i < depth; i++){
        accum += weight*this->noise(temp_p);
        weight *= 0.5f;
        temp_p *= 2.0f;
    }

    return fabs(accum);
}
