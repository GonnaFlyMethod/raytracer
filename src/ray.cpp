#include "ray.h"


Point3 Ray::GetOrigin() const{
    return origin;
}

Vec3 Ray::GetDirection() const {
    return direction;
}

Point3 Ray::at(double t) const {
    auto directionWithMagnitude = t *direction;
    return (Point3&)origin + (Vec3&)directionWithMagnitude;
}