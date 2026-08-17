#define _USE_MATH_DEFINES
#include "num_sys_fractal.h"
#include "../base_structs.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const double PI = M_PI;

std::vector<Line> num_sys::iterate(const std::vector<Line>& start_lines, std::vector<Line>& all_lines, float scaling, int num_sys) {
    std::vector<Line> new_lines = {};

    for (const Line& line : start_lines) {
        Line new_straight(
            line.end,
            line.end + sf::Vector2f{line.length * scaling, 0.f},
            line.length * scaling
        );

        new_lines.push_back(new_straight);
        all_lines.push_back(new_straight);

        for (int i = 1; i < num_sys; i++) {
            float angle = 2 * PI * i / num_sys;
            sf::Vector2f new_straight_end = new_straight.end;
            Line new_line(
                new_straight.start,
                {new_straight_end.x * std::cos(angle) - new_straight_end.y * std::sin(angle),
                 new_straight_end.x * std::sin(angle) + new_straight_end.y * std::cos(angle)},
                new_straight.length);
            
            new_lines.push_back(new_line);
            all_lines.push_back(new_line);
        }
    }
    
    return new_lines;
}

std::vector<Line> num_sys::simulate(int iterations, float scaling, int num_sys, int window_height) {
    Line straight(
            {0.f, 0.f},
            sf::Vector2f{window_height * 0.5f, 0.f},
            window_height * 0.5f
    );

    std::vector<Line> all_lines = {straight};
    sf::Vector2f straight_end = straight.end;


    for (int i = 1; i < num_sys; i++) {
            float angle = 2 * PI * i / num_sys;
            sf::Vector2f straight_end = straight.end;
            Line new_line(
                straight.start,
                {straight_end.x * std::cos(angle) - straight_end.y * std::sin(angle),
                 straight_end.x * std::sin(angle) + straight_end.y * std::cos(angle)},
                straight.length);
            all_lines.push_back(new_line);
    }

    std::vector<Line> start_lines = all_lines;

    for (int i = 0; i < iterations; i++) {
        start_lines = num_sys::iterate(start_lines, all_lines, scaling, num_sys);
    }

    return all_lines;
}