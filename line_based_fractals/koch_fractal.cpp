#include "koch_fractal.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> koch::iterate(const std::vector<Line>& prev_lines, float width_factor, float height_factor) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        float new_width = line.length * width_factor;
        float new_height = line.length * height_factor;
        float left_str_length = (line.length - new_width) / 2.f;
        sf::Vector2f l_breakpoint = line.point_on_line_from_start(left_str_length);
        sf::Vector2f r_breakpoint = line.point_on_line_from_start(line.length - left_str_length);

        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        sf::Vector2f middle = line.point_on_line_from_start (line.length / 2);
        sf::Vector2f middle_breakpoint = rotate_point_around_anchorpoint(
            middle - sf::Vector2f{0.f, new_height}, 
            middle, 
            angle_deg
        );

        Line left_str(
            line.start,
            l_breakpoint,
            left_str_length
        );

        Line right_str(
            r_breakpoint,
            line.end,
            left_str_length
        );

        Line left_diag(
            l_breakpoint,
            middle_breakpoint,
            new_height
        );

        Line right_diag(
            middle_breakpoint,
            r_breakpoint,
            new_height
        );
        next_lines.push_back(left_str);
        next_lines.push_back(right_str);
        next_lines.push_back(left_diag);
        next_lines.push_back(right_diag);
    }
    return next_lines;
}

std::vector<Line> koch::simulate(const Config& config) {
    std::vector<Line> lines = config.initial_line_vector;

    for (int i = 0; i < config.iterations; i++) {
        lines = koch::iterate(lines, config.line_model_width, config.line_model_height);
    }

    return lines;
}