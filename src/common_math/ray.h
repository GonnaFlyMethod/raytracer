#pragma once

#include "vec3.h"

namespace CommonMath{
    class Ray{
    private:
        CommonMath::Point3 origin;
        Vec3 direction;
        double time;
    public:

        Ray() =default;
        Ray(const CommonMath::Point3& orig, const Vec3& dir): origin(orig), direction(dir), time(0){};
        Ray(const CommonMath::Point3& orig, const Vec3& dir, double tm): origin(orig), direction(dir), time(tm){};

        CommonMath::Point3 GetOrigin() const;
        Vec3 GetDirection() const;
        double GetTime() const;

        CommonMath::Point3 at(double t) const;
    };
}

