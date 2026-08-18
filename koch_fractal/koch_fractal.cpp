#include "koch_fractal.h"

#include "../base_structs.h"
#include <SFML/Graphics.hpp>

#include <vector>


std::vector<Line> iterate(const std::vector<Line>& prev_lines, float scaling) {
    std::vector<Line> next_lines = {};

    for (const Line& line : prev_lines) {
        sf::Vector2f l_breakpoint = line.point_on_line_from_start(line.length / 3);
        sf::Vector2f r_breakpoint = line.point_on_line_from_start(2 * line.length / 3);
        sf::Vector2f middle = line.point_on_line_from_start (line.length / 2);

        Line left_str(
            line.start,
            l_breakpoint,
            line.length / 3
        );

        Line right_str(
            r_breakpoint,
            line.end,
            line.length / 3
        );

        Line left_diag(
            l_breakpoint,
            middle + sf::Vector2f(0.f, left_str.length * scaling),
            std::sqrt(std::pow(left_str.length * scaling, 2) + std::pow(line.length / 6, 2))
        );

        Line right_diag(
            middle + sf::Vector2f(0.f, left_str.length * scaling),
            r_breakpoint,
            std::sqrt(std::pow(left_str.length * scaling, 2) + std::pow(line.length / 6, 2))
        );
    }
}