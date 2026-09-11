#include "mandel_tree.h"

#include <SFML/Graphics.hpp>
#include <vector>

#include "../base_structs.h"
#include "../config.h"

std::vector<Line> mandel::iterate(const std::vector<Line>& prev_lines, std::vector<Line>& all_lines, float width_factor, float height_factor){
    std::vector<Line> next_lines = {};
    for(const Line& line : prev_lines) {
        sf::Vector2f left_bot = line.start;
        sf::Vector2f right_bot = line.end;
        sf::Vector2f middle = line.point_on_line_from_start(line.length / 2.f);

        //4 distances
        float offset = line.length * width_factor;
        float new_height = line.length * height_factor;
        float d1 = new_height + offset / 2.f;
        float d2 = new_height + offset;
        float d3 = d1 + offset;

        sf::Vector2f left_mid = left_bot - sf::Vector2f{0.f, new_height};
        sf::Vector2f right_mid = right_bot - sf::Vector2f{0.f, d1};
        sf::Vector2f left_top = left_bot - sf::Vector2f{0.f, d2};
        sf::Vector2f mid_bot = middle - sf::Vector2f{0.f, d2};
        sf::Vector2f mid_top = middle - sf::Vector2f{0.f, d3};
        sf::Vector2f right_top = right_bot - sf::Vector2f{0.f, d3};

        float angle_rad = std::atan2(line.end.y - line.start.y, line.end.x - line.start.x);
        float angle_deg = angle_rad * 360.f / (2 * PI);

        left_mid = rotate_point_around_anchorpoint(left_mid, left_bot, angle_deg);
        right_mid = rotate_point_around_anchorpoint(right_mid, right_bot, angle_deg);
        left_top = rotate_point_around_anchorpoint(left_top, left_bot, angle_deg);
        mid_bot = rotate_point_around_anchorpoint(mid_bot, middle, angle_deg);
        mid_top = rotate_point_around_anchorpoint(mid_top, middle, angle_deg);
        right_top = rotate_point_around_anchorpoint(right_top, right_bot, angle_deg);

        Line left(
            left_bot, left_mid, new_height
        );
        all_lines.push_back(left);

        Line left_empty(
            left_mid, left_top, offset
        );
        next_lines.push_back(left_empty);

        Line left_to_mid(
            left_top, mid_bot, line.length / 2.f
        );
        all_lines.push_back(left_to_mid);

        Line mid_up(
            mid_bot, mid_top, offset / 2.f
        );
        all_lines.push_back(mid_up);

        Line mid_to_right(
            mid_top, right_top, line.length / 2.f
        );
        all_lines.push_back(mid_to_right);

        Line right_empty(
            right_top, right_mid, offset
        );
        next_lines.push_back(right_empty);

        Line right(
            right_mid, right_bot, d1
        );
        all_lines.push_back(right);
    }
    return next_lines;
}

std::vector<Line> mandel::simulate(const Config& config) {
    std::vector<Line> start_lines = config.initial_line_vector;
    std::vector<Line> all_lines = start_lines;

    for (int i = 0; i < config.iterations; i++) {
        start_lines = mandel::iterate(start_lines, all_lines, config.line_model_width, config.line_model_height);
    }

    return all_lines;
}