#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include "spirals/spiral_structs.h"

const float PI = 3.14159265358979323846f;

struct Line{
    sf::Vector2f start;
    sf::Vector2f end;
    float length;

    Line(sf::Vector2f start_, sf::Vector2f end_, float length_)
        : start(start_), end(end_), length(length_) {}

    Line translate_copy(sf::Vector2f offset) {
        return Line(start + offset, end + offset, length);
    }

    sf::Vector2f point_on_line_from_start(float distance) const {
        //with interpolation
        float t = distance / length;
        return start + (end - start) * t;
    }
};

inline sf::Vector2f rotate_point_around_anchorpoint(sf::Vector2f target, const sf::Vector2f& anchor, float angle_deg) {
    //translate anchor to origin, do the same translation on target so that the rotation happens around the origin
    target -= sf::Vector2f{anchor.x, anchor.y};

    //rotate around origin with rotation matrix
    float angle_rad = angle_deg * 2 * PI / 360;
    float prev_x = target.x;
    float prev_y = target.y;
    target.x = prev_x * std::cos(angle_rad) - prev_y * std::sin(angle_rad);
    target.y = prev_y * std::cos(angle_rad) + prev_x * std::sin(angle_rad);

    //translate back
    target += sf::Vector2f{anchor.x, anchor.y};

    return target;
}