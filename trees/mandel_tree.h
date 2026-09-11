# pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"

namespace mandel{
    std::vector<Line> iterate(const std::vector<Line>& prev_lines, std::vector<Line>& all_lines, float width_factor, float height_factor);
    std::vector<Line> simulate(const Config& config);
}