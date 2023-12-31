#pragma once

namespace CommonMath{
    inline double clamp(double x, double min, double max){
        // Clamps value in the interval [min, max]

        if (x < min)return min;
        if (x > max) return max;
        return x;
    }

    inline double calculate_area_of_triangle (
            double length_of_a_side, double length_of_b_side, double length_of_c_side){

        double semi_perimeter = (length_of_a_side + length_of_b_side + length_of_c_side) / 2.0f;

        return sqrt(semi_perimeter *
                    (semi_perimeter - length_of_a_side) *
                    (semi_perimeter - length_of_b_side) *
                    (semi_perimeter -length_of_c_side));
    };
}

