#pragma once

#include <SFML/Graphics.hpp>

struct Line{
    sf::Vector2f start;
    sf::Vector2f end;
    float length;

    Line(sf::Vector2f start_, sf::Vector2f end_, float length_)
        : start(start_), end(end_), length(length_) {}

    Line translate_copy(sf::Vector2f offset) {
        return Line(start + offset, end + offset, length);
    }
};