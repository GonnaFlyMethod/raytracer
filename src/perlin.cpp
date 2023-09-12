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

// The linear interpolation can be described in the following general formula:
// B*(t) + A*(1-t), where's A is the starting point of interpolation and B is the end point.
// The t parameter shows the percentage in the range [A;B], where's t = 0 will yield A and t = 1 will yield
//  B. Suppose we have the following interval:

// 10(A)________________________________25(B)
// and we want to know what's the value in the middle of 10 and 25. Well, for this purpose we're
// using t parameter from the formula, but now it will be 0.5:
// A = 10,
// B = 25
// t = 0.5
// value = 25 * 0.5 + 10 * (1 - 0.5) = 17.5

// basically you can think about this formula (B*(t) + A*(1-t)) in the following way:
// 10(A)_______________x(t=0.5)________________25(B)
// while t = 0.5, A side and B side contribute equally to the final value, so while performing
// 1 - t in the formula you're still getting 0.5 -> 0.5 * A + 0.5 * A. This means "take contribution of A and add it
// to the contribution of B". Note that A and B can anything: colors, sounds, etc. but in this case we're dealing with
// abstract numbers. Let's assum that t=0.7
// 10(A)____________________________x(0.7)___________25(B)
// then this yield 20.5 as a value. It means: B contributes to the the final value on 70% while
// A is contributing on 30%, that's why we're flipping percentage in the formula -> 1-t.

// This was 1 dimension. In trilinear interpolation we're dealing with 3 dimensions. Each dimension contributes
// to the final result. In our case we're dealing with trilinear interpolation in the context of perlin samples.
// Think about the whole process as a cube. We have 8 perlin samples, so let's place this samples at the each corner of
// the cube. Basically, perlin samples are just doubles in the interval [0,1). where 0.2 will result eventually in a
// pretty dark color (almost black) and 0.9 will be near white. So we have generated the following samples:
//     0.2 o--------o 0.9
//        /|       /|
//       / |      / |
//  0.7 o----0.8-o  |
//      |  o-0.1-|--o 0.5
//      | /      | /
//      |/       |/
//  0.5 o--------o 0.1

// u, v and w shows us our position in the cube x = u, v = y, z = w. All of them are clamped naturally in the interval
// [0;1). Let u(aka x) = 0.78, v(aka y) = 0.22 and w(aka z) = 0.33. Then the nearest cube's corner for us will be this one:

//     o--------o
//    /|       /|
//   / |      / |
//  o--------o  |
//  |  o-----|--o
//  | /      | /
//  |/       |/
//  o--------o <- this one

// This perlin sample(0.1) will contribute to the final result more than any other one.
// Now what does accum += (i*u + (1-i)*(1-u))*
//                            (j*v + (1-j)*(1-v))*
//                            (k*w + (1-k)*(1-w))*c[i][j][k] mean?
// It can be dived onto 2 parts the percentage of contribution of each perlin sample:
// (i*u + (1-i)*(1-u))*
// (j*v + (1-j)*(1-v))*
// (k*w + (1-k)*(1-w))
//
// and the perlin samples itself:
// c[i][j][k]

// think about it in this way. We're calculating the percentage of contribution of each corner based on
// u(aka x), v(aka y), w(aka z). For examples for u = 0.78, v = 0.22, w = 0.3 the contribution percentage will
// be the following:
//   0.014 o--------o 0.05
//        /|       /|
//       / |      / |
// 0.03 o---0.12-o  |
//      |  o-0.05|--o 0.1825
//      | /      | /
//      |/       |/
// 0.120o--------o 0.425 <- pay attention how this corner contributes more to the final result
// All percentages should form 1 while summed together. Now, this percentages are multiplied with perlin samples:

//      P0.014 * S0.2 o-----------------o P0.05 * S0.9
//                   /|                /|
//                  / |               / |
//    P0.03 * S0.7 o------P0.12*S0.8-o  |
//                 |  o-P0.05*S0.1---|--o P0.1825 * S0.5
//                 | /               |  /
//                 |/                | /
//                 |                 |/
//     P0.5*S0.120 o-----------------o  P0.425 * S0.1
//
// P denotes percentage of contribution and S denotes perlin sample.
// accum += (i*u + (1-i)*(1-u))*
//          (j*v + (1-j)*(1-v))*
//          (k*w + (1-k)*(1-w))*c[i][j][k]
//
// So on each iteration we're calculating percentage of contribution for each cube's corner and multiplying
// the percentage on the perlin  sample and then add contribution of each cube's corner together.
// Number of iteration = number of cube's corner:
//
//       4 o--------o 8
//        /|       /|
//       / |      / |
//   3  o------7-o  |
//      |  o-2---|--o 6
//      | /      | /
//      |/       |/
//    1 o--------o 5
//
// Additionally, + sign in linear interpolation plays the same role in the
// trilinear one (in our case + is accum +=).

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
