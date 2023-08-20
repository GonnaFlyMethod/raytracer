#include "vec3.h"
#include "common_math.h"

using std::sqrt;

Vec3::Vec3(double x, double y, double z) {
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
}

double Vec3::x() const {
    return this->data[0];
}

double Vec3::y() const {
    return this->data[1];
}

double Vec3::z() const {
    return this->data[2];
}

Vec3 Vec3::random() {
    return {random_double(), random_double(), random_double()};
}

Vec3 Vec3::random(double min, double max) {
    return {random_double(min, max), random_double(min, max),random_double(min, max)};
}

bool Vec3::near_zero(){
    const double threshold = 1e-8;
    return (fabs(data[0]) < threshold) && (fabs(data[1]) < threshold) && (fabs(data[2]) < threshold);
}

Vec3 Vec3::operator-() const {
    return {-data[0], -data[1], -data[2]};
}

double Vec3::operator[](int i ) const{
    return data[i];
}

double& Vec3::operator[](int i ){
    return data[i];
}

Vec3& Vec3::operator+=(const Vec3& other) {
    data[0] += other[0];
    data[1] += other[1];
    data[2] += other[2];

    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
    data[0] -= other[0];
    data[1] -= other[1];
    data[2] -= other[2];

    return *this;
}

Vec3& Vec3::operator*=(const double val){
    data[0] *= val;
    data[1] *= val;
    data[2] *= val;

    return *this;
}

Vec3& Vec3::operator/=(const double val){
    return *this *= 1/val;
}

double Vec3::length(){
    return sqrt(length_squared());
}

double Vec3::length_squared(){
    double Xsqrd = data[0] * data[0];
    double Ysqrd = data[1] * data[1];
    double Zsqrd = data[2] * data[2];

    return Xsqrd + Ysqrd + Zsqrd;
}

// Vec3 utility
std::ostream& operator<<(std::ostream& out, const Vec3& v){
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

Vec3 operator+(const Vec3& u, const Vec3& v){
    return {
            u.x() + v.x(),
            u.y() + v.y(),
            u.z() + v.z()
    };
}

Vec3 operator-(const Vec3& u, const Vec3& v){
    return {
            u.x() - v.x(),
            u.y() - v.y(),
            u.z() - v.z()
    };
}

Vec3 operator*(const Vec3& u, const Vec3& v){
    return {
            u.x() * v.x(),
            u.y() * v.y(),
            u.z() * v.z()
    };
}

Vec3 operator*(const double t, const Vec3& v){
    return {
            t * v.x(),
            t * v.y(),
            t * v.z()
    };
}

Vec3 operator*(const Vec3& v, const double t){
    return t * v;
}

Vec3 operator/(const Vec3& v, const double t){
    return (1/t) * v;
}


Vec3 reflect(const Vec3& r, const Vec3& n){
    return r - 2*dot(r,n)*n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double eta_over_eta_prime){
    double cost_theta = fmin(dot(-uv, n), 1.0f);

    Vec3 ray_perpendicular = eta_over_eta_prime * (uv + cost_theta * n);
    Vec3 ray_parallel = -sqrt(fabs(1.0 - ray_perpendicular.length_squared())) * n;

    return ray_perpendicular + ray_parallel;
}

double dot(const Vec3& a, const Vec3& b){
    return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
}

Vec3 cross(const Vec3& a, const Vec3& b){
    return {
            a.y() * b.z() - b.y() * a.z(),
            b.x() * a.z() - a.x() * b.z(),
            a.x()* b.y() - b.x() * a.y()
    };
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

Vec3 random_in_unit_sphere(){
    while (true){
        Vec3 p = Vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_unit_disk(){
    while (true){
        Vec3 random_vec2D = Vec3(random_double(-1, 1), random_double(-1, 1), 0.0f);

        if (random_vec2D.length_squared() < 1){
            return random_vec2D;
        }
    }
}

Vec3 random_in_hemisphere(Vec3 normal){
    Vec3 in_unit_sphere = random_in_unit_sphere();

    if (dot(normal, in_unit_sphere) > 0.0f){
        return in_unit_sphere;
    }else{
        return -in_unit_sphere;
    }
}
