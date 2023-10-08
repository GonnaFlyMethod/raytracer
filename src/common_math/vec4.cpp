#include "vec4.h"

namespace CommonMath{
    Vec4::Vec4(double x, double y, double z, double w){
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
    }

    Vec4::Vec4(std::vector<double> v){
        this->data[0] = v[0];
        this->data[1] = v[1];
        this->data[2] = v[2];
        this->data[3] = v[3];
    }

    double Vec4::x() const {
        return this->data[0];
    }

    double Vec4::y() const {
        return this->data[1];
    }

    double Vec4::z() const {
        return this->data[2];
    }

    double Vec4::w() const {
        return this->data[3];
    }

    double Vec4::operator[](int i ) const{
        return data[i];
    }

    double& Vec4::operator[](int i ){
        return data[i];
    }

    Vec4 operator*(const Mat4& m, const Vec4& v){
        Vec4 result;

        result[0] = (m[0][0] * v[0]) + (m[0][1] * v[1]) + (m[0][2] * v[2]) + (m[0][3] * v[3]);
        result[1] = (m[1][0] * v[0]) + (m[1][1] * v[1]) + (m[1][2] * v[2]) + (m[1][3] * v[3]);
        result[0] = (m[2][0] * v[0]) + (m[2][1] * v[1]) + (m[2][2] * v[2]) + (m[2][3] * v[3]);
        result[0] = (m[3][0] * v[0]) + (m[3][1] * v[1]) + (m[3][2] * v[2]) + (m[3][3] * v[3]);

        return result;
    }

    Vec4 operator*(const double t, const Vec4& v){
        return {
                t * v.x(),
                t * v.y(),
                t * v.z(),
                t * v.w()
        };
    }

    Vec4 operator*(const Vec4& v, const double t){
        return t * v;
    }

    Vec4 operator+(const Vec4& v1, const Vec4& v2){
        return {
                v1.x() + v2.x(),
                v1.y() + v2.y(),
                v1.z() + v2.z(),
                v1.w() + v2.w(),
        };
    }
}