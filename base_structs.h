#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

const float PI = static_cast<float>(M_PI);

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
        //calculate the formula of the line: y = ax + b
        // b = y1 - ax1  -->  y2 = ax2 + y1 - ax1  -->  a = (y2 - y1) / (x2 - x1)
        float a = (end.y - start.y) / (end.x - start.x);
        float b = start.y - a * start.x;

        //use intersection with a circle centered on start with radius = distance
        // (x - c)^2 + (y - d)^2 = dist^2
        // (x - c)^2 + (ax + b - d)^2 = dist^2
        // e = b - d
        // x^2 - 2xc + c^2 + a^2x^2 + 2axe + e^2 = dist^2
        //(1 + a^2)x^2 + (-2c + 2ae)x + c^2 + e^2 - dist^2 = 0
        //use discriminant for the rest
        float c = start.x;
        float d = start.y;
        float e = b - d;

        float disc_a = 1 + std::pow(a, 2.f);
        float disc_b = 2 * a * e - 2 * c;
        float disc_c = std::pow(c, 2.f) + std::pow(e, 2.f) - std::pow(distance, 2.f);

        float disc =  std::pow(disc_c, 2.f) - 4 * disc_a * disc_c;

        float x = (-1 * disc_b + std::sqrt(disc)) / (2 * disc_a);
        if ((x > start.x && x < end.x) || (x < start.x && x > end.x)) {
            return {x, a * x + b};
        }

        x = (-1 * disc_b - std::sqrt(disc)) / (2 * disc_a);
        return {x, a * x + b};
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