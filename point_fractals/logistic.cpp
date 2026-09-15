#include "logistic.h"

#include <SFML/Graphics.hpp>
#include <vector>

#include "../config.h"

void logistic::iterate(const Config& c, double a, std::vector<sf::Vertex>& draw_points) {
    std::vector<sf::Vertex> samples;
    samples.reserve(c.samples);
    double xn = c.x0;

    for (int i = 0; i < c.trash_iterations; i++) {
        xn = a * xn * (1 - xn);
    }
    for (int sample = 0; sample < c.samples; sample++) {
        xn = a * xn * (1 - xn);
        draw_points.push_back(sf::Vertex{{static_cast<float>(a * 100), static_cast<float>(xn * 100)}});
    }
    std::cout << "Calculated: a = " << a << '\n';
}

std::vector<sf::Vertex> logistic::simulate(const Config& c) {
    std::vector<sf::Vertex> draw_points;
    int vector_space = (static_cast<int>((c.a_end - c.a_start) / c.stepsize) + 1) * c.samples;
    draw_points.reserve(vector_space);

    double a = c.a_start;
    while (a < c.a_end){
        iterate(c, a, draw_points);
        a += c.stepsize;
    }
    return draw_points;
}