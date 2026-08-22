#include "mink.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> mink::iterate(const std::vector<Line>& prev_lines, float width_factor, float height_factor) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        float new_width = line.length * width_factor;
        float new_height = line.length * height_factor;
        sf::Vector2f l_breakpoint = line.point_on_line_from_start(line.length - new_width);
        sf::Vector2f r_breakpoint = line.point_on_line_from_start(new_width);

        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        sf::Vector2f middle = line.point_on_line_from_start (line.length / 2);
        sf::Vector2f middle_top = rotate_point_around_anchorpoint(
            middle - sf::Vector2f{0.f, new_height}, 
            middle, 
            angle_deg
        );

        sf::Vector2f middle_bottom = rotate_point_around_anchorpoint(
            middle + sf::Vector2f{0.f, new_height}, 
            middle, 
            angle_deg
        );

        sf::Vector2f left_top = rotate_point_around_anchorpoint(
            l_breakpoint - sf::Vector2f{0.f, new_height}, 
            l_breakpoint, 
            angle_deg
        );

        sf::Vector2f right_bottom = rotate_point_around_anchorpoint(
            r_breakpoint + sf::Vector2f{0.f, new_height}, 
            r_breakpoint, 
            angle_deg
        );

        Line left_str(
            line.start,
            l_breakpoint,
            line.length - new_width
        );

        Line left_up(
            l_breakpoint,
            left_top,
            new_height
        );

        Line left_top_str(
            l_breakpoint,
            middle_top,
            new_width / 2.f
        );

        Line vert(
            middle_top,
            middle_bottom,
            new_height * 2.f
        );

        Line right_bottom_str(
            middle_bottom,
            right_bottom,
            new_width / 2.f
        );

        Line right_down(
            right_bottom,
            r_breakpoint,
            new_height
        );

        Line right_str(
            r_breakpoint,
            line.end,
            line.length - new_width
        );

        next_lines.push_back(left_str);
        next_lines.push_back(left_up);
        next_lines.push_back(left_top_str);
        next_lines.push_back(vert);
        next_lines.push_back(right_bottom_str);
        next_lines.push_back(right_down);
        next_lines.push_back(right_str);
    }
    return next_lines;
}

std::vector<Line> mink::simulate(const Config& config) {
    std::vector<Line> lines = config.initial_line_vector;

    for (int i = 0; i < config.iterations; i++) {
        lines = mink::iterate(lines, config.line_model_width, config.line_model_height);
    }

    return lines;
}