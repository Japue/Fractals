# pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"

namespace dragon{
    void iterate(std::vector<Line>& all_lines, float rotation_angle);
    std::vector<Line> simulate(const Config& config);
}
