#include "num_sys_fractal.h"
#include "../base_structs.h"
#include "../config.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

std::vector<Line> num_sys::iterate(const std::vector<Line>& start_lines, std::vector<Line>& all_lines, float scaling, int num_sys) {
    std::vector<Line> new_lines = {};

    for (const Line& line : start_lines) {
        Line new_straight(
            line.end,
            line.end - sf::Vector2f{0.f, line.length * scaling},
            line.length * scaling
        );

        new_lines.push_back(new_straight);
        all_lines.push_back(new_straight);

        for (int i = 1; i < num_sys; i++) {
            float angle = 360.f * i / num_sys;
            Line new_line(
                new_straight.start,
                rotate_point_around_anchorpoint(new_straight.end, new_straight.start, angle),
                new_straight.length);
            
            new_lines.push_back(new_line);
            all_lines.push_back(new_line);
        }
    }
    
    return new_lines;
}

std::vector<Line> num_sys::simulate(const Config& config) {
    Line straight(
            {0.f, 0.f},
            sf::Vector2f{0.f, config.window_height * -0.5f},
            config.window_height * 0.5f
    );

    std::vector<Line> all_lines = {straight};
    sf::Vector2f straight_end = straight.end;


    for (int i = 1; i < config.num_sys; i++) {
            float angle = 360.f * i / config.num_sys;
            Line new_line(
                straight.start,
                rotate_point_around_anchorpoint(straight.end, straight.start, angle),
                straight.length);
            all_lines.push_back(new_line);
    }

    std::vector<Line> start_lines = all_lines;

    for (int i = 0; i < config.iterations; i++) {
        start_lines = num_sys::iterate(start_lines, all_lines, config.scaling, config.num_sys);
    }

    return all_lines;
}