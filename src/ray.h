#pragma once

#include "vec3.h"

class Ray{
private:
    Point3 origin;
    Vec3 direction;
    double time;
public:

    Ray() =default;
    Ray(const Point3& orig, const Vec3& dir): origin(orig), direction(dir), time(0){};
    Ray(const Point3& orig, const Vec3& dir, double tm): origin(orig), direction(dir), time(tm){};

    Point3 GetOrigin() const;
    Vec3 GetDirection() const;
    double GetTime() const;

    Point3 at(double t) const;
};
