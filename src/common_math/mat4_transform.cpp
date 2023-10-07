#include "mat4_transform.h"

namespace CommonMath{
    Mat4 look_at_for_view_projection(Vec3 eye, Vec3 center, Vec3 up){
        // The transformation is suitable for right hand coordinate system

        const Vec3 f = (center - eye).normalize();
        const Vec3 s = cross(f, up).normalize();
        const Vec3 u = cross(s, f);

        Mat4 result;

        result[0][0] = s.x();
        result[1][0] = s.y();
        result[2][0] = s.z();
        result[0][1] = u.x();
        result[1][1] = u.y();
        result[2][1] = u.z();
        result[0][2] =-f.x();
        result[1][2] =-f.y();
        result[2][2] =-f.z();
        result[3][0] =-dot(s, eye);
        result[3][1] =-dot(u, eye);
        result[3][2] = dot(f, eye);

        return result;
    }

    Mat4 orthographic_projection(double left, double right, double bottom, double top, double zNear, double zFar){
        // The transformation is suitable for right hand coordinate system

        Mat4 result;

        result[0][0] = 2.0 / (right - left);
        result[1][1] = 2.0 / (top - bottom);
        result[2][2] = -2.0 / (zFar - zNear);
        result[3][0] = -(right + left) / (right - left);
        result[3][1] = -(top + bottom) / (top - bottom);
        result[3][2] = -(zFar + zNear) / (zFar - zNear);
        return result;
    }

}