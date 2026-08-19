#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../base_structs.h"
#include "../config.h"

struct H{
    Line hori;
    Line left;
    Line right;

    H(Line hori_, Line left_, Line right_) : hori (hori_), left (left_), right (right_) {}
};

namespace hfrac
{
std::vector<H> iterate(const std::vector<H> &begin_h, std::vector<H> &all_h, float scaling);
std::vector<Line> simulate(const Config& config);
}
