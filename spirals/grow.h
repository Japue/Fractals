#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"
#include "spiral_structs.h"

#include <vector>

namespace grow{
    Line iterate(const PolarPoint prev_point, float scaling, float angle);
    std::vector<Line> simulate(const Config& config);
}