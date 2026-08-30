#include "lightning.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> lightning::iterate(const std::vector<Line>& prev_lines, float width_factor, float height_factor) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        float new_width = line.length * width_factor;
        float new_height = line.length * height_factor;
        float breakpoint_width = (line.length - new_width) / 2.f;

        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        sf::Vector2f l_breakpoint_on_line = line.point_on_line_from_start(breakpoint_width);
        sf::Vector2f r_breakpoint_on_line = line.point_on_line_from_start(line.length - breakpoint_width);

        sf::Vector2f l_breakpoint = l_breakpoint_on_line + sf::Vector2f{0.f, new_height};
        sf::Vector2f r_breakpoint = r_breakpoint_on_line - sf::Vector2f{0.f, new_height};

        rotate_point_around_anchorpoint(l_breakpoint, l_breakpoint_on_line, angle_deg);
        rotate_point_around_anchorpoint(r_breakpoint, r_breakpoint_on_line, angle_deg);

        Line one(
            line.start, 
            l_breakpoint,
            std::sqrt(std::pow(line.start.x - l_breakpoint.x, 2.f) + std::pow(line.start.y - l_breakpoint.y, 2.f))
        );


        Line two(
            l_breakpoint,
            r_breakpoint,
            std::sqrt(std::pow(l_breakpoint.x - r_breakpoint.x, 2.f) + std::pow(l_breakpoint.y - r_breakpoint.y, 2.f))
        );

        Line three(
            r_breakpoint,
            line.end,
            std::sqrt(std::pow(r_breakpoint.x - line.end.x, 2.f) + std::pow(r_breakpoint.y - line.end.y, 2.f))
        );

        next_lines.push_back(one);
        next_lines.push_back(two);
        next_lines.push_back(three);
    }
    return next_lines;
}

std::vector<Line> lightning::simulate(const Config& config) {
    std::vector<Line> lines = config.initial_line_vector;

    for (int i = 0; i < config.iterations; i++) {
        lines = lightning::iterate(lines, config.line_model_width, config.line_model_height);
    }

    return lines;
}