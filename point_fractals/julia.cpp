#include "julia.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

#include "../config.h"

void julia::iterate(const Config& c, double x0, double y0, std::vector<sf::Vertex>& draw_points) {
    double xn = x0 * x0 - y0 * y0 + c.a;
    double yn = 2 * x0 * y0 + c.b;
    int steps = 0;

    while (xn * xn + yn * yn < 4 && steps < c.p_iterations){
        double xnew = xn * xn - yn * yn + c.a;
        double ynew = 2 * xn * yn + c.b;

        xn = xnew;
        yn = ynew;
        steps++;
    }
    sf::Vertex point;
    point.position = sf::Vector2f{static_cast<float>(x0), static_cast<float>(y0)};

    double v;
    if (steps >= c.p_iterations) {
        v = c.p_iterations;
    } else {
        double log_zn = std::log(xn * xn + yn * yn) / 2.0;
        v = steps + 1 - std::log(log_zn) / std::log(2.0);
        if (v < 0) v = 0;
        if (v > c.p_iterations) v = c.p_iterations;
    }
    double band = std::fmod(v, c.band_colors) / c.band_colors;

    point.color = sf::Color(static_cast<std::uint8_t>(255 * (1 - band)), 0, static_cast<std::uint8_t>(255 * band));
    draw_points.push_back(point);
    std::cout << "Point made: (" << x0 << ", " << y0 << ")" << '\n';
}

std::vector<sf::Vertex> julia::simulate(const Config& c) {
    std::vector<sf::Vertex> draw_points;
    double x_start = c.x_start;
    double x_end = c.x_end;
    double y_start = c.y_start;
    double y_end = c.y_end;

    int x_points = static_cast<int>((x_end - x_start) / c.x_stepsize);
    int y_points = static_cast<int>((y_end - y_start) / c.y_stepsize);
    draw_points.reserve(static_cast<size_t>(x_points * y_points));

    for(double x = x_start; x < x_end; x += c.x_stepsize) {
        for(double y = y_start; y < y_end; y += c.y_stepsize) {
            julia::iterate(c, x, y, draw_points);
        }
    }
    return draw_points;
}