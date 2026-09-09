# pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"

namespace pyth{
    Line square(Line bottom_line, std::vector<Line>& all_lines);
    void triangle(Line bottom_line, std::vector<Line>& next_lines, std::vector<Line>& all_lines, float width_factor, float height_factor);
    std::vector<Line> iterate(const std::vector<Line>& prev_lines, std::vector<Line>& all_lines, float triangle_width_factor, float triangle_height_factor);
    std::vector<Line> simulate(const Config& config);
}