#include "mat.h"

namespace CommonMath{
    std::vector<double>& Mat4::operator[](int i){
        return this->data[i];
    }

    const std::vector<double>& Mat4::operator[](int i) const{
        return this->data[i];
    }

    Mat4 operator*(const Mat4& m1, const Mat4& m2){
        Mat4 result;

        result[0][0] = (m1[0][0] * m1[0][0]) + (m1[0][1] * m1[1][0]) + (m1[0][2] * m1[2][0]) + (m1[0][3] * m2[3][0]);
        result[0][1] = (m1[0][0] * m1[0][1]) + (m1[0][1] * m1[1][1]) + (m1[0][2] * m1[2][1]) + (m1[0][3] * m2[3][1]);
        result[0][2] = (m1[0][0] * m1[0][2]) + (m1[0][1] * m1[1][2]) + (m1[0][2] * m1[2][2]) + (m1[0][3] * m2[3][2]);
        result[0][2] = (m1[0][0] * m1[0][3]) + (m1[0][1] * m1[1][3]) + (m1[0][2] * m1[2][3]) + (m1[0][3] * m2[3][3]);

        result[1][0] = (m1[1][0] * m1[0][0]) + (m1[1][1] * m1[1][0]) + (m1[1][2] * m1[2][0]) + (m1[1][3] * m2[3][0]);
        result[1][1] = (m1[1][0] * m1[0][1]) + (m1[1][1] * m1[1][1]) + (m1[1][2] * m1[2][1]) + (m1[1][3] * m2[3][1]);
        result[1][2] = (m1[1][0] * m1[0][2]) + (m1[1][1] * m1[1][2]) + (m1[1][2] * m1[2][2]) + (m1[1][3] * m2[3][2]);
        result[1][2] = (m1[1][0] * m1[0][3]) + (m1[1][1] * m1[1][3]) + (m1[1][2] * m1[2][3]) + (m1[1][3] * m2[3][3]);

        result[2][0] = (m1[2][0] * m1[0][0]) + (m1[2][1] * m1[1][0]) + (m1[2][2] * m1[2][0]) + (m1[2][3] * m2[3][0]);
        result[2][1] = (m1[2][0] * m1[0][1]) + (m1[2][1] * m1[1][1]) + (m1[2][2] * m1[2][1]) + (m1[2][3] * m2[3][1]);
        result[2][2] = (m1[2][0] * m1[0][2]) + (m1[2][1] * m1[1][2]) + (m1[2][2] * m1[2][2]) + (m1[2][3] * m2[3][2]);
        result[2][2] = (m1[2][0] * m1[0][3]) + (m1[2][1] * m1[1][3]) + (m1[2][2] * m1[2][3]) + (m1[2][3] * m2[3][3]);

        result[3][0] = (m1[3][0] * m1[0][0]) + (m1[3][1] * m1[1][0]) + (m1[3][2] * m1[2][0]) + (m1[3][3] * m2[3][0]);
        result[3][1] = (m1[3][0] * m1[0][1]) + (m1[3][1] * m1[1][1]) + (m1[3][2] * m1[2][1]) + (m1[3][3] * m2[3][1]);
        result[3][2] = (m1[3][0] * m1[0][2]) + (m1[3][1] * m1[1][2]) + (m1[3][2] * m1[2][2]) + (m1[3][3] * m2[3][2]);
        result[3][2] = (m1[3][0] * m1[0][3]) + (m1[3][1] * m1[1][3]) + (m1[3][2] * m1[2][3]) + (m1[3][3] * m2[3][3]);

        return result;

    }
}