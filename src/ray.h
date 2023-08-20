#pragma once

#include "vec3.h"

class Ray{
public:
    Point3 origin;
    Vec3 direction;

    Ray() =default;
    Ray(const Point3& orig, const Vec3& dir): origin(orig), direction(dir){}

    Point3 GetOrigin() const;
    Vec3 GetDirection() const;

    Point3 at(double t) const;
};
