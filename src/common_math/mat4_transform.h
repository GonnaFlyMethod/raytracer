#pragma once

#include "mat4.h"

namespace CommonMath{
    Mat4 look_at_for_view_projection(Vec3& eye, Vec3& center, Vec3& up);
    Mat4 orthographic_projection(double left, double right, double bottom, double top, double zNear, double zFar);
}
