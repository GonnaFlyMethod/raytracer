#pragma once

#include "mat.h"

namespace CommonMath{
    Mat4 look_at_for_view_projection(Vec3& eye, Vec3& center, Vec3& up);
}
