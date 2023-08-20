#pragma once

#include <vector>
#include <cmath>
#include <iostream>

class Vec3{
private:
    std::vector<double> data {0,0,0};

public:
    Vec3() =default;
    Vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    static Vec3 random();
    static Vec3 random(double min, double max);

    bool near_zero();

    Vec3 operator-() const;
    double operator[](int i ) const;
    double& operator[](int i );
    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(const double val);
    Vec3& operator/=(const double val);

    double length();
    double length_squared();

};

// Type aliases for Vec3
using Point3 = Vec3;
using Color = Vec3;


// Vec3 utility
std::ostream& operator<<(std::ostream& out, const Vec3& v);

Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(const double t, const Vec3& v);
Vec3 operator*(const Vec3& v, const double t);
Vec3 operator/(const Vec3& v, const double t);

Vec3 reflect(const Vec3& r, const Vec3& n);
Vec3 refract(const Vec3& uv, const Vec3& n, double eta_over_eta_prime);

double dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);

Vec3 unit_vector(Vec3 v);

Vec3 random_in_unit_sphere();
Vec3 random_unit_vector();
Vec3 random_in_unit_disk();
Vec3 random_in_hemisphere(Vec3 normal);
