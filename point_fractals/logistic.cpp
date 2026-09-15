#include "logistic.h"

#include <SFML/Graphics.hpp>
#include <vector>

#include "../config.h"

void logistic::iterate(const Config& c, double a, std::vector<sf::Vertex>& draw_points) {
    std::vector<sf::Vertex> samples;
    samples.reserve(c.l_samples);
    double xn = c.l_x0;

    for (int i = 0; i < c.l_trash_iterations; i++) {
        xn = a * xn * (1 - xn);
    }
    for (int sample = 0; sample < c.l_samples; sample++) {
        xn = a * xn * (1 - xn);
        draw_points.push_back(sf::Vertex{{static_cast<float>(a * 100), static_cast<float>(xn * 100)}});
    }
    std::cout << "Calculated: a = " << a << '\n';
}

std::vector<sf::Vertex> logistic::simulate(const Config& c) {
    std::vector<sf::Vertex> draw_points;
    int vector_space = (static_cast<int>((c.l_a_end - c.l_a_start) / c.l_stepsize) + 1) * c.l_samples;
    draw_points.reserve(vector_space);

    double a = c.l_a_start;
    while (a < c.l_a_end){
        iterate(c, a, draw_points);
        a += c.l_stepsize;
    }
    return draw_points;
}