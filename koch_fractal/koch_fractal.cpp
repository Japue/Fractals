#include "koch_fractal.h"

#include "../base_structs.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> koch::iterate(const std::vector<Line>& prev_lines, float scaling) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        sf::Vector2f l_breakpoint = line.point_on_line_from_start(line.length / 3);
        sf::Vector2f r_breakpoint = line.point_on_line_from_start(2 * line.length / 3);

        float new_line_length = line.length / 3;
        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        sf::Vector2f middle = line.point_on_line_from_start (line.length / 2);
        sf::Vector2f middle_breakpoint = rotate_point_around_anchorpoint(
            middle - sf::Vector2f{0.f, new_line_length * scaling}, 
            middle, 
            angle_deg
        );

        Line left_str(
            line.start,
            l_breakpoint,
            new_line_length
        );

        Line right_str(
            r_breakpoint,
            line.end,
            line.length / 3
        );

        Line left_diag(
            l_breakpoint,
            middle_breakpoint,
            std::sqrt(std::pow(left_str.length * scaling, 2.f) + std::pow(line.length / 6, 2.f))
        );

        Line right_diag(
            middle_breakpoint,
            r_breakpoint,
            std::sqrt(std::pow(left_str.length * scaling, 2.f) + std::pow(line.length / 6, 2.f))
        );
        next_lines.push_back(left_str);
        next_lines.push_back(right_str);
        next_lines.push_back(left_diag);
        next_lines.push_back(right_diag);
    }
    return next_lines;
}

std::vector<Line> koch::simulate(int iterations, float scaling, int window_height) {
    std::vector<Line> lines = {Line({-0.5f * window_height, 0.f}, {0.5f * window_height, 0.f}, 1.f * window_height)};

    for (int i = 0; i < iterations; i++) {
        lines = koch::iterate(lines, scaling);
    }

    return lines;
}