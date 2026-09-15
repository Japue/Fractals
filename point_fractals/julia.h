#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../config.h"

namespace julia {
    void iterate(const Config& c, double x0, double y0, std::vector<sf::Vertex>& draw_points);
    std::vector<sf::Vertex> simulate(const Config& c);
}