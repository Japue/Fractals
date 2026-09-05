#include "grow.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"
#include "spiral_structs.h"

#include <vector>

Line grow::iterate(const PolarPoint prev_point, float scaling, float angle) {
    PolarPoint next_point(prev_point.r * scaling, prev_point.angle + angle);
    //we dont care for the length here
    return Line(prev_point.to_sfVector(), next_point.to_sfVector(), 0.f);
}

std::vector<Line> grow::simulate(const Config& config){
    std::vector<Line> all_lines = {};
    float base_length = 200.f;
    PolarPoint start_point (base_length, 0.f);

    for (int i = 0; i < config.iterations; i++) {
        Line new_line = grow::iterate(start_point, config.spiral_scaling, config.spiral_angle);
        start_point = PolarPoint(new_line.end);
        all_lines.push_back(new_line);
    }

    return all_lines;
}