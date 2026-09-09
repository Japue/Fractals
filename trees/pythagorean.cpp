#include "pythagorean.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>

Line pyth::square(Line bottom_line, std::vector<Line>& all_lines){
    float length = bottom_line.length;
    sf::Vector2f left_offset = bottom_line.start - sf::Vector2f{0.f, length};
    sf::Vector2f right_offset = bottom_line.end - sf::Vector2f{0.f, length};

    float angle_rad = std::atan2(bottom_line.end.y - bottom_line.start.y, bottom_line.end.x - bottom_line.start.x);
    float angle_deg = angle_rad * 360.f / (2 * PI);
    sf::Vector2f top_left = rotate_point_around_anchorpoint(left_offset, bottom_line.start, angle_deg);
    sf::Vector2f top_right = rotate_point_around_anchorpoint(right_offset, bottom_line.end, angle_deg);

    all_lines.push_back(Line(
        bottom_line.start,
        top_left,
        length
    ));

    all_lines.push_back(Line(
        bottom_line.end,
        top_right,
        length
    ));

    all_lines.push_back(Line(
        top_left,
        top_right,
        length
    ));

    return Line(top_left, top_right, length);
}


void pyth::triangle(Line bottom_line, std::vector<Line>& next_lines, std::vector<Line>& all_lines, float width_factor, float height_factor){
    float new_width = (width_factor - 0.5f) * bottom_line.length;
    float new_height = bottom_line.length * height_factor;

    sf::Vector2f middle = bottom_line.point_on_line_from_start(bottom_line.length / 2.f);
    sf::Vector2f offset_top = middle + sf::Vector2f{new_width, -new_height};
 
    float angle_rad = std::atan2(bottom_line.end.y - bottom_line.start.y, bottom_line.end.x - bottom_line.start.x);
    float angle_deg = angle_rad * 360.f / (2 * PI);
    sf::Vector2f top = rotate_point_around_anchorpoint(offset_top, middle, angle_deg);

    Line left(
        bottom_line.start,
        top,
        std::sqrt(std::pow(bottom_line.start.x - top.x, 2.f) + std::pow(bottom_line.start.y - top.y, 2.f))
    );

    Line right(
        top,
        bottom_line.end,
        std::sqrt(std::pow(bottom_line.end.x - top.x, 2.f) + std::pow(bottom_line.end.y - top.y, 2.f))
    );

    next_lines.push_back(left);
    next_lines.push_back(right);
    all_lines.push_back(left);
    all_lines.push_back(right);
}

std::vector<Line> pyth::iterate(const std::vector<Line>& prev_lines, std::vector<Line>& all_lines, float triangle_width_factor, float triangle_height_factor){
    std::vector<Line> next_lines = {};
    for (Line line : prev_lines) {
        Line triangle_bottom = pyth::square(line, all_lines);
        pyth::triangle(triangle_bottom, next_lines, all_lines, triangle_width_factor, triangle_height_factor);
    }
    return next_lines;
}

std::vector<Line> pyth::simulate(const Config& config){
    std::vector<Line> start_lines = config.initial_line_vector;
    std::vector<Line> all_lines = start_lines;

    for (int i = 0; i < config.iterations; i++) {
        start_lines = pyth::iterate(start_lines, all_lines, config.line_model_width, config.line_model_height);
    }

    return all_lines;
}