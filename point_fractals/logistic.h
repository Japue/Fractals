#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../config.h"

namespace logistic {
    void iterate(const Config& c, double a, std::vector<sf::Vertex>& draw_points);
    std::vector<sf::Vertex> simulate(const Config& c);
}