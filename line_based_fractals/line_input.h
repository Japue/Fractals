#pragma once

#include <vector>
#include "../base_structs.h"

enum class InitialLines {
    custom,
    oneline,
    twoline,
    triangle,
    sideways_triangle,
    reverse_triangle,
    square,
    reverse_square,
    rhombus,
    hexagon,
    octagon,
    reverse_octagon,
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
    } else if (str == "sideways triangle") {
        return InitialLines::sideways_triangle;
    } else if (str == "reverse triangle") {
        return InitialLines::reverse_triangle;
    } else if (str == "square") {
        return InitialLines::square;
    } else if (str == "reverse square") {
        return InitialLines::reverse_square;
    } else if (str == "rhombus") {
        return InitialLines::rhombus;
    } else if (str == "hexagon") {
        return InitialLines::hexagon;
    } else if (str == "octagon") {
        return InitialLines::octagon;
    } else if (str == "reverse octagon") {
        return InitialLines::reverse_octagon;
    }
    return InitialLines::none;
}

inline std::vector<Line> line_input(InitialLines initial_line_input, toml::table tbl, int window_height) {
    std::vector<Line> initial_line_vector = {};
    switch (initial_line_input) {
        case InitialLines::custom: {
            toml::array* arr = tbl["custom_lines"].as_array();
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

        case InitialLines::sideways_triangle: {
            Line left({-200.f, 300.f}, {-200.f, -300.f}, 600.f);
            Line top({-200.f, -300.f}, {std::sqrt(std::pow(600.f, 2.f) - std::pow(300.f, 2.f)) - 200.f, 0.f}, 600.f);
            Line bottom({std::sqrt(std::pow(600.f, 2.f) - std::pow(300.f, 2.f)) - 200.f, 0.f}, {-200.f, 300.f}, 600.f);
            initial_line_vector.push_back(left);
            initial_line_vector.push_back(top);
            initial_line_vector.push_back(bottom);
            break;
        }

        case InitialLines::reverse_triangle: {
            Line hor(
                {-300.f, 200.f}, 
                {300.f, 200.f}, 
                600.f
            );
            Line left(
                {0, -1.f * std::sqrt(std::pow(600.f, 2.f) - std::pow(300.f, 2.f)) + 200.f},
                {-300.f, 200.f}, 
                600.f
            );
            Line right(
                {300.f, 200.f},
                {0, -1.f * std::sqrt(std::pow(600.f, 2.f) - std::pow(300.f, 2.f)) + 200.f},
                600.f
            );
            initial_line_vector.push_back(hor);
            initial_line_vector.push_back(left);
            initial_line_vector.push_back(right);
            break;
        }

        case InitialLines::square: {
            Line top({-300, -300}, {300, -300}, 600.f);
            Line right({300, -300}, {300, 300}, 600.f);
            Line bot({300, 300}, {-300, 300}, 600.f);
            Line left({-300, 300}, {-300, -300}, 600.f);
            initial_line_vector.push_back(top);
            initial_line_vector.push_back(right);
            initial_line_vector.push_back(bot);
            initial_line_vector.push_back(left);
            break;
        }

        case InitialLines::reverse_square: {
            Line top({300, -300}, {-300, -300}, 600.f);
            Line right({300, 300}, {300, -300}, 600.f);
            Line bot({-300, 300}, {300, 300}, 600.f);
            Line left({-300, -300}, {-300, 300}, 600.f);
            initial_line_vector.push_back(top);
            initial_line_vector.push_back(right);
            initial_line_vector.push_back(bot);
            initial_line_vector.push_back(left);
            break;
        }

        case InitialLines::rhombus: {
            float length = std::sqrt(2.f) * 400.f;
            Line top_left({0.f, -400.f}, {-400.f, 0.f}, length);
            Line bottom_left({-400.f, 0.f}, {0.f, 400.f}, length);
            Line bottom_right({0.f, 400.f}, {400.f, 0.f}, length);
            Line top_right({400.f, 0.f}, {0.f, -400.f}, length);
            initial_line_vector.push_back(top_left);
            initial_line_vector.push_back(bottom_left);
            initial_line_vector.push_back(bottom_right);
            initial_line_vector.push_back(top_right);
            break;
        }

        case InitialLines::hexagon: {
            float x = 400.f;
            float l = x / std::cos(PI / 6.f);
            float distance_to_vertex = std::sqrt(std::pow(l, 2.f) - std::pow(x, 2.f)) + l / 2.f;

            Line left({-x, l/2.f}, {-x, -l/2.f}, l);
            Line top_left({-x, -l/2.f}, {0.f, -distance_to_vertex}, l);
            Line top_right({0.f, -distance_to_vertex}, {x, -l/2.f}, l);
            Line right({x, -l/2.f}, {x, l/2.f}, l);
            Line bottom_right({x, l/2.f}, {0.f, distance_to_vertex}, l);
            Line bottom_left({0.f, distance_to_vertex}, {-x, l/2.f}, l);

            initial_line_vector.push_back(left);
            initial_line_vector.push_back(top_left);
            initial_line_vector.push_back(top_right);
            initial_line_vector.push_back(right);
            initial_line_vector.push_back(bottom_right);
            initial_line_vector.push_back(bottom_left);
            break;
        }

        case InitialLines::octagon: {
            float l = 800.f;
            float x = (l / std::sqrt(2.f)) + (l / 2.f);
            Line top({-400.f, -x}, {400.f, -x}, l);
            Line top_right({400.f, -x}, {x, -400.f}, l);
            Line right({x, -400.f}, {x, 400.f}, l);
            Line right_bottom({x, 400.f}, {400.f, x}, l);
            Line bottom({400.f, x}, {-400.f, x}, l);
            Line bottom_left({-400.f, x}, {-x, 400.f}, l);
            Line left({-x, 400.f}, {-x, -400.f}, l);
            Line left_top({-x, -400.f}, {-400.f, -x}, l);
            initial_line_vector.push_back(top);
            initial_line_vector.push_back(top_right);
            initial_line_vector.push_back(right);
            initial_line_vector.push_back(right_bottom);
            initial_line_vector.push_back(bottom);
            initial_line_vector.push_back(bottom_left);
            initial_line_vector.push_back(left);
            initial_line_vector.push_back(left_top);
            break;
        }

        case InitialLines::reverse_octagon: {
            float l = 800.f;
            float x = (l / std::sqrt(2.f)) + (l / 2.f);
            Line top({400.f, -x}, {-400.f, -x}, l);
            Line top_right({x, -400.f}, {400.f, -x}, l);
            Line right({x, 400.f}, {x, -400.f}, l);
            Line right_bottom({400.f, x}, {x, 400.f}, l);
            Line bottom({-400.f, x}, {400.f, x}, l);
            Line bottom_left({-x, 400.f}, {-400.f, x}, l);
            Line left({-x, -400.f}, {-x, 400.f}, l);
            Line left_top({-400.f, -x}, {-x, -400.f}, l);
            initial_line_vector.push_back(top);
            initial_line_vector.push_back(top_right);
            initial_line_vector.push_back(right);
            initial_line_vector.push_back(right_bottom);
            initial_line_vector.push_back(bottom);
            initial_line_vector.push_back(bottom_left);
            initial_line_vector.push_back(left);
            initial_line_vector.push_back(left_top);
            break;
        }

        case InitialLines::none: {
            std::cerr << "Not a valid argument for premade_preset" << "\n";
            break;
        }
    }
    return initial_line_vector;
}