#include "simple_tree.h"
#include "../base_structs.h"

std::vector<Line> iterate(const std::vector<Line>& begin_lines, std::vector<Line> &all_lines, float scaling) {
    std::vector<Line> next_lines = {};

    for (const Line line : begin_lines) {
        Line hor_line(
            {line.end.x - line.length / 2, line.end.y}, {
            line.end.x + line.length / 2, line.end.y}, 
            line.length);
        all_lines.push_back(hor_line);

        float new_length = hor_line.length * scaling;

        Line l_line(
            hor_line.start,
            hor_line.start - sf::Vector2f{0.f, new_length},
            new_length);
        next_lines.push_back(l_line);
        all_lines.push_back(l_line);

        Line r_line(
            hor_line.end,
            hor_line.end - sf::Vector2f{0.f, new_length},
            new_length);
        next_lines.push_back(r_line);
        all_lines.push_back(r_line);
    }
    return next_lines;
}

std::vector<Line> simulate(int iterations, float scaling, int window_height) {
    std::vector<Line> all_lines = {
        Line({0.f, window_height / 2.f}, {0.f, 0.f}, window_height / 2.f)};
    std::vector<Line> start_lines = all_lines;

    for (int i = 0; i < iterations; i++) {
        start_lines = iterate(start_lines, all_lines, scaling);
    }

    return all_lines;
}