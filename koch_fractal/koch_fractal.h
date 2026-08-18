# pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"

namespace koch{
    std::vector<Line> iterate(const std::vector<Line>& prev_lines, float scaling);
    std::vector<Line> simulate(int iterations, float scaling, int window_height);
}