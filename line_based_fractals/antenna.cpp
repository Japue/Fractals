#include "antenna.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> antenna::iterate(const std::vector<Line>& prev_lines, float width_factor, float height_factor) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        float new_width = line.length * width_factor;
        float new_height = line.length * height_factor;

        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        sf::Vector2f middle = line.point_on_line_from_start (line.length / 2);

        sf::Vector2f left_point = rotate_point_around_anchorpoint(
            middle - sf::Vector2f(new_width / 2.f, new_height),
            middle,
            angle_deg
        );

        sf::Vector2f right_point = rotate_point_around_anchorpoint(
            middle - sf::Vector2f(-1.f * new_width / 2.f, new_height),
            middle,
            angle_deg
        );

        float new_length = std::sqrt(std::pow(new_width / 2.f, 2.f) + std::pow(new_height, 2.f));

        Line left(line.start, middle, line.length / 2.f);
        Line right(middle, line.end, line.length / 2.f);
        Line left_diag_to(middle, left_point, new_length);
        Line left_diag_from(left_point, middle, new_length);
        Line right_diag_to(middle, right_point, new_length);
        Line right_diag_from(right_point, middle, new_length);

        next_lines.push_back(left);
        next_lines.push_back(right);
        next_lines.push_back(left_diag_to);
        next_lines.push_back(left_diag_from);
        next_lines.push_back(right_diag_to);
        next_lines.push_back(right_diag_from);
    }
    return next_lines;
}

std::vector<Line> antenna::simulate(const Config& config) {
    std::vector<Line> lines = config.initial_line_vector;

    for (int i = 0; i < config.iterations; i++) {
        lines = antenna::iterate(lines, config.line_model_width, config.line_model_height);
    }

    return lines;
}