#pragma once

#include <vector>
#include "vec3.h"

namespace CommonMath{
    class Mat4 {
        private:
            std::vector<std::vector<double>> data = std::vector<std::vector<double>>{
                    std::vector<double>{1.0, 0.0, 0.0, 0.0},
                    std::vector<double>{0.0, 1.0, 0.0, 0.0},
                    std::vector<double>{0.0, 0.0, 1.0, 0.0},
                    std::vector<double>{0.0, 0.0, 0.0, 1.0}
            };

        public:
            Mat4() = default;
            std::vector<double>& operator[](int i);
            const std::vector<double>& operator[](int i) const;
    };

    Mat4 operator*(const Mat4& m1, const Mat4& m2);
}
