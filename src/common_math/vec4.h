#pragma once

#include <vector>
#include "mat4.h"

namespace CommonMath{
    class Vec4 {
        private:
            std::vector<double> data{0.0, 0.0, 0.0, 0.0};
    public:
        Vec4() = default;
        Vec4(double x, double y, double z, double w);
        Vec4(std::vector<double> v);

        double x() const;
        double y() const;
        double z() const;
        double w() const;

        double operator[](int i ) const;
        double& operator[](int i );
    };

    Vec4 operator*(const Mat4& m, const Vec4& v);

    Vec4 operator*(const double t, const Vec4& v);
    Vec4 operator*(const Vec4& v, const double t);

    Vec4 operator+(const Vec4& v1, const Vec4& v2);
}
