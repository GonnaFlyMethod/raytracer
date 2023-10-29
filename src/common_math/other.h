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

    inline double distance(double num_a, double num_b){
        if (num_a < 0 && num_b > 0 || num_a > 0 && num_b < 0){
            return std::abs(num_a) + std::abs(num_b);
        }

        return std::abs(std::abs(num_a) - std::abs(num_b));
    }
}

