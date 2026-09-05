#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "../config.h"

struct PolarPoint {
    float r;
    float angle;

    PolarPoint(float r_, float angle_) : r (r_), angle (angle_) {}

    PolarPoint(sf::Vector2f sfpoint) : 
        r (std::sqrt(std::pow(sfpoint.x, 2.f) + std::pow(sfpoint.y, 2.f))),
        angle (std::atan2(-sfpoint.y, sfpoint.x))
        {}

    sf::Vector2f to_sfVector() const {
        float angle_rad = angle * 2.f * 3.14159265358979323846f / 360.f;
        return sf::Vector2f{r * std::cos(angle_rad), -r * std::sin(angle_rad)};
    }
};