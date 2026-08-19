#pragma once

#include <vector>
#include "../base_structs.h"

enum class InitialLines {
    custom,
    oneline,
    twoline,
    triangle,
    none
};

inline InitialLines initial_line_conv(std::string_view str) {
    if (str == "custom") {
        return InitialLines::custom;
    } else if (str == "one line") {
        return InitialLines::oneline;
    } else if (str == "two lines") {
        return InitialLines::twoline;
    } else if (str == "triangle") {
        return InitialLines::triangle;
    }
    return InitialLines::none;
}

inline std::vector<Line> line_input(InitialLines initial_line_input, toml::table tbl, int window_height) {
    std::vector<Line> initial_line_vector = {};
    switch (initial_line_input) {
        case InitialLines::custom: {
            toml::array* arr = tbl["initial_lines"].as_array();
            for (auto&& line : *arr) {
                toml::array* points_arr = line.as_array();
                toml::array* start_arr = (*points_arr)[0].as_array();
                toml::array* end_arr = (*points_arr)[1].as_array();

                float start_x = start_arr->get(0)->value_or(0.f);
                float start_y = start_arr->get(1)->value_or(0.f);
                float end_x = end_arr->get(0)->value_or(0.f);
                float end_y = end_arr->get(1)->value_or(0.f);

                initial_line_vector.push_back(Line(
                    {start_x, start_y}, 
                    {end_x, end_y}, 
                    std::sqrt(std::pow(end_x - start_x, 2.f) + std::pow(end_y - start_y, 2.f))
                ));
            }
            break;
        }

        case InitialLines::oneline: {
            Line line({window_height / -4.f, 0.f}, {window_height / 4.f, 0.f}, window_height / 2.f);
            initial_line_vector.push_back(line);
            break;
        }

        case InitialLines::twoline: {
            Line line_up({window_height / -4.f, 0.f}, {window_height / 4.f, 0.f}, window_height / 2.f);
            Line line_down({window_height / 4.f, 0.f}, {window_height / -4.f, 0.f}, window_height / 2.f);
            initial_line_vector.push_back(line_up);
            initial_line_vector.push_back(line_down);
            break;
        }

        case InitialLines::triangle: {
            Line hor(
                {300.f, 200.f}, 
                {-300.f, 200.f}, 
                600.f
            );
            Line left(
                {-300.f, 200.f}, 
                {0, -1.f * std::sqrt(std::pow(600.f, 2.f) - std::pow(300.f, 2.f)) + 200.f},
                600.f
            );
            Line right(
                {0, -1.f * std::sqrt(std::pow(600.f, 2.f) - std::pow(300.f, 2.f)) + 200.f},
                {300.f, 200.f},
                600.f
            );
            initial_line_vector.push_back(hor);
            initial_line_vector.push_back(left);
            initial_line_vector.push_back(right);
            break;
        }

        case InitialLines::none: {
            std::cerr << "Not a valid argument for premade_preset" << "\n";
            break;
        }
    }
    return initial_line_vector;
}