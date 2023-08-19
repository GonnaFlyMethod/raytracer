#pragma once

#include "vec3.h"

class Ray{
public:
    Point3 origin;
    Vec3 direction;

    Ray() =default;

    Ray(const Point3& orig, const Vec3& dir)
        : origin(orig), direction(dir){}

    [[nodiscard]] Point3 GetOrigin() const{
        return origin;
    }

    [[nodiscard]] Vec3 GetDirection() const{
        return direction;
    }

    [[nodiscard]] Point3 at(double t) const{
        auto directionWithMagnitude = t *direction;
        return (Point3&)origin + (Vec3&)directionWithMagnitude;
    }
};
