#pragma once

#include <vector>
#include "vec3.h"
#include "vec4.h"

namespace CommonMath{
    class Mat4 {
        private:
            std::vector<Vec4> data = std::vector<Vec4>{
                    Vec4{1.0, 0.0, 0.0, 0.0},
                    Vec4{0.0, 1.0, 0.0, 0.0},
                    Vec4{0.0, 0.0, 1.0, 0.0},
                    Vec4{0.0, 0.0, 0.0, 1.0}
            };

        public:
            Mat4() = default;

            Vec4& operator[](int i);
            const Vec4& operator[](int i) const;
    };

    Mat4 operator*(const Mat4& m1, const Mat4& m2);
}
