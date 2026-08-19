#pragma once

#include <vector>
#include "../base_structs.h"
#include "../config.h"

namespace simple_tree
{
    std::vector<Line> iterate(const std::vector<Line>& begin_lines, std::vector<Line> &all_lines, float scaling);
    std::vector<Line> simulate(const Config& config);
}