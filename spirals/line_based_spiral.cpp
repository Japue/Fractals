#include "line_based_spiral.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"
#include "spiral_structs.h"

#include <vector>

std::vector<Line> line_spiral::iterate(const std::vector<Line>& prev_lines, std::vector<Line>& all_lines, float scaling, float angle){
    std::vector<Line> next_lines = {};
    for(const Line& line : prev_lines) {
        PolarPoint polar_start(line.start);
        sf::Vector2f new_start = PolarPoint(polar_start.r * scaling, polar_start.angle + angle).to_sfVector();

        PolarPoint polar_end(line.end);
        sf::Vector2f new_end = PolarPoint(polar_end.r * scaling, polar_end.angle + angle).to_sfVector();

        float new_length = scaling * line.length;

        Line new_line(
            new_start,
            new_end,
            new_length
        );
        next_lines.push_back(new_line);
        all_lines.push_back(new_line);
    }

    return next_lines;
}

std::vector<Line> line_spiral::simulate(const Config& config){
    std::vector<Line> start_lines = config.initial_line_vector;
    std::vector<Line> all_lines = start_lines;

    for (int i = 0; i < config.iterations; i++) {
        start_lines = iterate(start_lines, all_lines, config.spiral_scaling, config.spiral_angle);
    }
    return all_lines;
}