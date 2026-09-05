#include "dragon.h"

#include "../base_structs.h"
#include "../config.h"
#include <SFML/Graphics.hpp>

#include <vector>

void dragon::iterate(std::vector<Line>& all_lines, float rotation_angle){
    Line last_line(*(all_lines.end() - 1));
    sf::Vector2f anchor = last_line.start;
    int vector_size = static_cast<int>(all_lines.size());

    for (int line_index = 0; line_index < vector_size; line_index++) {
        Line line = all_lines.at(vector_size - line_index - 1);
        Line new_line(
            rotate_point_around_anchorpoint(line.end, anchor, -rotation_angle),
            rotate_point_around_anchorpoint(line.start, anchor, -rotation_angle),
            line.length
        );

        all_lines.push_back(new_line);
    }
}

std::vector<Line> dragon::simulate(const Config& config){
    std::vector<Line> lines = config.initial_line_vector;

    for (int i = 0; i < config.iterations; i++) {
        dragon::iterate(lines, config.rotation_angle);
    }

    return lines;
}