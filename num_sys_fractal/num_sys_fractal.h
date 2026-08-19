#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../base_structs.h"
#include "../config.h"

namespace num_sys {
    std::vector<Line> iterate(const std::vector<Line>& start_lines, std::vector<Line>& all_lines, float scaling, int num_sys);
    std::vector<Line> simulate(const Config& config);
}