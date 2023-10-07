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

        double x() const;
        double y() const;
        double z() const;
        double w() const;

        double operator[](int i ) const;
        double& operator[](int i );
    };

    Vec4 operator*(const Mat4& m, const Vec4& v);
}
