#pragma once

#include <vector>
#include "../base_structs.h"

std::vector<Line> iterate(const std::vector<Line>& begin_lines, std::vector<Line> &all_lines, float scaling);

std::vector<Line> simulate(int iterations, float scaling, float window_height);