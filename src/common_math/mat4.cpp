#include "mat4.h"
#include "vec4.h"

namespace CommonMath{
    CommonMath::Vec4& Mat4::operator[](int i){
        return this->data[i];
    }

    const CommonMath::Vec4& Mat4::operator[](int i) const{
        return this->data[i];
    }

    Mat4 operator*(const Mat4& m1, const Mat4& m2){
        // Column major order

        CommonMath::Vec4 first_row_first_mat = CommonMath::Vec4(m1[0]);
        CommonMath::Vec4 second_row_first_mat = CommonMath::Vec4(m1[1]);
        CommonMath::Vec4 third_row_first_mat = CommonMath::Vec4(m1[2]);
        CommonMath::Vec4 fourth_row_first_mat = CommonMath::Vec4(m1[3]);

        CommonMath::Vec4 first_row_second_mat = CommonMath::Vec4(m2[0]);
        CommonMath::Vec4 second_row_second_mat = CommonMath::Vec4(m2[1]);
        CommonMath::Vec4 third_row_second_mat = CommonMath::Vec4(m2[2]);
        CommonMath::Vec4 fourth_row_second_mat = CommonMath::Vec4(m2[3]);

        Mat4 result;
        result[0] = (first_row_first_mat * first_row_second_mat[0]) +
                    (second_row_first_mat * first_row_second_mat[1]) +
                    (third_row_first_mat * first_row_second_mat[2]) +
                    (fourth_row_first_mat * first_row_second_mat[3]);

        result[1] = (first_row_first_mat * second_row_second_mat[0]) +
                    (second_row_first_mat * second_row_second_mat[1]) +
                    (third_row_first_mat * second_row_second_mat[2]) +
                    (fourth_row_first_mat * second_row_second_mat[3]);

        result[2] = (first_row_first_mat * third_row_second_mat[0]) +
                    (second_row_first_mat * third_row_second_mat[1]) +
                    (third_row_first_mat * third_row_second_mat[2]) +
                    (fourth_row_first_mat * third_row_second_mat[3]);

        result[3] = (first_row_first_mat * fourth_row_second_mat[0]) +
                    (second_row_first_mat * fourth_row_second_mat[1]) +
                    (third_row_first_mat * fourth_row_second_mat[2]) +
                    (fourth_row_first_mat * fourth_row_second_mat[3]);

//        // 1st row
//        result[0][0] = (m1[0][0] * m2[0][0]) + (m1[0][1] * m2[1][0]) + (m1[0][2] * m2[2][0]) + (m1[0][3] * m2[3][0]);
//        result[0][1] = (m1[0][0] * m2[0][1]) + (m1[0][1] * m2[1][1]) + (m1[0][2] * m2[2][1]) + (m1[0][3] * m2[3][1]);
//        result[0][2] = (m1[0][0] * m2[0][2]) + (m1[0][1] * m2[1][2]) + (m1[0][2] * m2[2][2]) + (m1[0][3] * m2[3][2]);
//        result[0][3] = (m1[0][0] * m2[0][3]) + (m1[0][1] * m2[1][3]) + (m1[0][2] * m2[2][3]) + (m1[0][3] * m2[3][3]);
//
//        // 2nd row
//        result[1][0] = (m1[1][0] * m2[0][0]) + (m1[1][1] * m2[1][0]) + (m1[1][2] * m2[2][0]) + (m1[1][3] * m2[3][0]);
//        result[1][1] = (m1[1][0] * m2[0][1]) + (m1[1][1] * m2[1][1]) + (m1[1][2] * m2[2][1]) + (m1[1][3] * m2[3][1]);
//        result[1][2] = (m1[1][0] * m2[0][2]) + (m1[1][1] * m2[1][2]) + (m1[1][2] * m2[2][2]) + (m1[1][3] * m2[3][2]);
//        result[1][3] = (m1[1][0] * m2[0][3]) + (m1[1][1] * m2[1][3]) + (m1[1][2] * m2[2][3]) + (m1[1][3] * m2[3][3]);
//
//        // 3rd row
//        result[2][0] = (m1[2][0] * m2[0][0]) + (m1[2][1] * m2[1][0]) + (m1[2][2] * m2[2][0]) + (m1[2][3] * m2[3][0]);
//        result[2][1] = (m1[2][0] * m2[0][1]) + (m1[2][1] * m2[1][1]) + (m1[2][2] * m2[2][1]) + (m1[2][3] * m2[3][1]);
//        result[2][2] = (m1[2][0] * m2[0][2]) + (m1[2][1] * m2[1][2]) + (m1[2][2] * m2[2][2]) + (m1[2][3] * m2[3][2]);
//        result[2][3] = (m1[2][0] * m2[0][3]) + (m1[2][1] * m2[1][3]) + (m1[2][2] * m2[2][3]) + (m1[2][3] * m2[3][3]);
//
//        // 4th row
//        result[3][0] = (m1[3][0] * m2[0][0]) + (m1[3][1] * m2[1][0]) + (m1[3][2] * m2[2][0]) + (m1[3][3] * m2[3][0]);
//        result[3][1] = (m1[3][0] * m2[0][1]) + (m1[3][1] * m2[1][1]) + (m1[3][2] * m2[2][1]) + (m1[3][3] * m2[3][1]);
//        result[3][2] = (m1[3][0] * m2[0][2]) + (m1[3][1] * m2[1][2]) + (m1[3][2] * m2[2][2]) + (m1[3][3] * m2[3][2]);
//        result[3][3] = (m1[3][0] * m2[0][3]) + (m1[3][1] * m2[1][3]) + (m1[3][2] * m2[2][3]) + (m1[3][3] * m2[3][3]);

        return result;

    }
}