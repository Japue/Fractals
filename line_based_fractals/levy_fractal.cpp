#include "levy_fractal.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> levy::iterate(const std::vector<Line>& prev_lines, float height_factor) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        float new_height = line.length * height_factor;
        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        sf::Vector2f middle = line.point_on_line_from_start (line.length / 2);
        sf::Vector2f middle_breakpoint = rotate_point_around_anchorpoint(
            middle - sf::Vector2f{0.f, new_height}, 
            middle, 
            angle_deg
        );

        Line left(
            line.start,
            middle_breakpoint,
            std::sqrt(std::pow(line.length / 2.f, 2.f) + std::pow(new_height, 2.f))
        );

        Line right(
            middle_breakpoint,
            line.end,
            std::sqrt(std::pow(line.length / 2.f, 2.f) + std::pow(new_height, 2.f))
        );

        next_lines.push_back(left);
        next_lines.push_back(right);
    }
    return next_lines;
}

std::vector<Line> levy::simulate(const Config& config) {
    std::vector<Line> lines = config.initial_line_vector;

    for (int i = 0; i < config.iterations; i++) {
        lines = levy::iterate(lines, config.line_model_height);
    }

    return lines;
}