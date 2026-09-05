#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"
#include "spiral_structs.h"

#include <vector>

namespace line_spiral{
    std::vector<Line> iterate(const std::vector<Line>& prev_lines, std::vector<Line>& all_lines, float scaling, float angle);
    std::vector<Line> simulate(const Config& config);
}