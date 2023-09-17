#include "ray.h"


Point3 Ray::GetOrigin() const{
    return origin;
}

Vec3 Ray::GetDirection() const {
    return direction;
}

double Ray::GetTime() const {
    return time;
}

Point3 Ray::at(double t) const {
    auto direction_with_magnitude = t * direction;
    return (Point3&)origin + (Vec3&)direction_with_magnitude;
}